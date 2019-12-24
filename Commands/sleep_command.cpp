#ifndef SLEEP_COMMAND_CPP
#define SLEEP_COMMAND_CPP
#include <chrono>
#include <thread>
#include "../command.h"
int Command::SleepMeth(string args[])
{
    std::this_thread::sleep_for(std::chrono::milliseconds(stoi(args[0])));
    return 0;
}
#endif