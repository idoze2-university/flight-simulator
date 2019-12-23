#ifndef DB_CPP
#define DB_CPP
#include "DB.h"

DB::DB()
{
    _command_names[Command::OpenDataServerStr] = Command(Command::OpenDataServer);
    _command_names[Command::ConnectControlClientStr] = Command(Command::ConnectControlClient);
    _command_names[Command::VarMethStr] = Command(Command::DefineVar);
    // _command_names[Command::PrintMethStr] = Command(PrintMeth);
    // _command_names[Command::SleepMethStr] = Command(SleepMeth);
    // _command_names[Command::WhileMethStr] = Command(WhileMeth);
    // _command_names[Command::IfMethStr] = Command(IfMeth);
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
    try
    {
        return _command_names[key];
    }
    catch (const std::exception &e)
    {
        std::cout << "Command: " << key << " is not defined." << endl;
        return NULL;
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
string DB::getNextUpdateQuery()
{
    auto entry = _update_queue.front();
    string _ret;
    _ret += "set ";
    _ret += entry.first + " ";
    _ret += entry.second;
    return _ret;
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
void DB::enqueueUpdate(string server_ver, double value)
{
    updateEntry entry = updateEntry(server_ver, value);
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
#endif