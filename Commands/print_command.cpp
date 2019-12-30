#ifndef PRINT_COMMAND_CPP
#define PRINT_COMMAND_CPP
#include "../parser.h"
#include "../command.h"
int Command::PrintMeth(string args[])
{
    auto arg = args[0];
    try
    {
        arg = to_string(Parser::parseValue(arg));
    }
    catch (const std::exception &e)
    {
    }
    arg.erase(remove(arg.begin(), arg.end(), '\"'), arg.end());
    return 0;
}
#endif