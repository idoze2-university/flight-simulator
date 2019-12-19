#ifndef DB_CPP
#define DB_CPP
#include "DB.h"
DB::DB()
{
    _command_names[Command::OpenDataServerStr] = Command(Command::OpenDataServer);
    //_command_names[Command::ConnectControlClientStr] = Command(Command::ConnectControlClient);
    // _command_names[Command::VarMethStr] = Command(VarMeth);
    // _command_names[Command::PrintMethStr] = Command(PrintMeth);
    // _command_names[Command::SleepMethStr] = Command(SleepMeth);
    // _command_names[Command::WhileMethStr] = Command(WhileMeth);
    // _command_names[Command::IfMethStr] = Command(IfMeth);
}

void DB::lockMutex()
{
    global_lock.lock();
}
void DB::unlockMutex()
{
    global_lock.unlock();
}
Command DB::getCommand(string key)
{
    return _command_names[key];
}
double DB::getServerValue(string key)
{
    lockMutex();
    return _server_values[key];
    unlockMutex();
}
#endif