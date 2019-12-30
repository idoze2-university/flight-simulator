#ifndef SLEEP_COMMAND_CPP
#define SLEEP_COMMAND_CPP
#include <chrono>
#include <thread>
#include "../parser.h"
#include "../command.h"
int Command::SleepMeth(string args[])
{
    auto arg = stoi(args[0]);
    try
    {
        arg = Parser::parseValue(args[0]);
    }
    catch (const std::exception &e)
    {
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(arg));
    return 0;
}
#endif