#ifndef DB_CPP
#define DB_CPP
#include "DB.h"

DB::DB()
{
    _command_names[Command::OpenDataServerStr] = Command(Command::OpenDataServer);
    _command_names[Command::ConnectControlClientStr] = Command(Command::ConnectControlClient);
    _command_names[Command::VarMethStr] = Command(Command::DefineVar);
    _command_names[Command::PrintMethStr] = Command(Command::PrintMeth);
    _command_names[Command::SleepMethStr] = Command(Command::SleepMeth);
    _command_names[Command::WhileMethStr] = Command(Command::WhileMeth);
    // _command_names[Command::IfMethStr] = Command(Command::IfMeth);
    names[0] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    names[1] = "/sim/time/warp";
    names[2] = "/controls/switches/magnetos";
    names[3] = "/instrumentation/heading-indicator/offset-deg";
    names[4] = "/instrumentation/altimeter/indicated-altitude-ft";
    names[5] = "/instrumentation/altimeter/pressure-alt-ft";
    names[6] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    names[7] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    names[8] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    names[9] = "/instrumentation/attitude-indicator/internal-roll-deg";
    names[10] = "/instrumentation/encoder/indicated-altitude-ft";
    names[11] = "/instrumentation/encoder/pressure-alt-ft";
    names[12] = "/instrumentation/gps/indicated-altitude-ft";
    names[13] = "/instrumentation/gps/indicated-ground-speed-kt";
    names[14] = "/instrumentation/gps/indicated-vertical-speed";
    names[15] = "/instrumentation/heading-indicator/indicated-heading-deg";
    names[16] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    names[17] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    names[18] = "/instrumentation/turn-indicator/indicated-turn-rate";
    names[19] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    names[20] = "/controls/flight/aileron";
    names[21] = "/controls/flight/elevator";
    names[22] = "/controls/flight/rudder";
    names[23] = "/controls/flight/flaps";
    names[24] = "/controls/engines/engine/throttle";
    names[25] = "/controls/engines/current-engine/throttle";
    names[26] = "/controls/switches/master-avionics";
    names[27] = "/controls/switches/starter";
    names[28] = "/engines/active-engine/auto-start";
    names[29] = "/controls/flight/speedbrake";
    names[30] = "/sim/model/c172p/brake-parking";
    names[31] = "/controls/engines/engine/primer";
    names[32] = "/controls/engines/current-engine/mixture";
    names[33] = "/controls/switches/master-bat";
    names[34] = "/controls/switches/master-alt";
    names[35] = "/engines/engine/rpm";
}

//-- Mutex
void DB::lockMutex()
{
    global_lock.lock();
}
void DB::unlockMutex()
{
    global_lock.unlock();
}

//-- Getters
Command DB::getCommand(string key)
{
    if (_command_names.find(key) != _command_names.end())
    {
        return _command_names[key];
    }
    else
    {
        throw "Invalid command name";
    }
}
double DB::getServerValue(string key)
{
    try
    {
        return _server_values[key];
    }
    catch (const std::exception &e)
    {
        std::cout << "Server value: " << key << " is not defined." << endl;
        return -1;
    }
}
double DB::getSymbol(string symbol)
{
    try
    {
        if (symbol.substr(0, 4) == "sim(")
        {
            return _server_values[symbol];
        }
        return _symbol_table[symbol];
    }
    catch (const std::exception &e)
    {
        std::cout << "Symbol: " << symbol << " is not defined." << endl;
        return -1;
    }
}
string DB::getBinding(string key)
{
    return _symbol_binding[key];
}
char *DB::getNextUpdateQuery()
{
    auto entry = _update_queue.front();
    if (entry.first.size())
    {
        string _ret;
        _ret += "setd ";
        _ret += entry.first + " \'";
        _ret += to_string(entry.second) + "\'";
        auto ret = new char[_ret.size()];
        strcpy(ret, _ret.c_str());
        _update_queue.pop();
        return ret;
    }
    else
    {
        return nullptr;
    }
}

//-- Setters
void DB::setBinding(string key, string value)
{
    _symbol_binding.emplace(key, value);
}

bool DB::isBound(string key)
{
    return _symbol_binding.find(key) != _symbol_binding.end();
}
void DB::enqueueUpdate(string server_var, double value)
{
    auto var = server_var.substr(6, server_var.size() - 8);
    updateEntry entry = updateEntry(var, value);
    _update_queue.push(entry);
}
void DB::setSymbol(string symbol, double value)
{
    //recursively set value to binding.
    if (isBound(symbol))
    {
        setSymbol(getBinding(symbol), value);
    }
    if (symbol.substr(0, 4) == "sim(")
    {
        enqueueUpdate(symbol, value);
    }
    _symbol_table[symbol] = value;
}
void DB::setServerValues(char *values)
{
    lockMutex();
    string str = string(values);
    regex exp("(\\b[-]?[0-9]*\\.[0-9]+\\b)");
    smatch res;
    for (int i = 0; regex_search(str, res, exp); i++, str = res.suffix())
    {
        _server_values.emplace(names[i], stod(res[0]));
    }
    unlockMutex();
}
#endif