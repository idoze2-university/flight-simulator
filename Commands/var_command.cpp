#ifndef VAR_COMMAND_CPP
#define VAR_COMMAND_CPP
#include "../command.h"
#include "../parser.h"
#include "../DB.h"
int Command::DefineVar(string args[])
{
    auto var1 = args[0];
    auto binding = args[1];
    auto var2 = args[2];
    if (binding == BindRTL)
    {
        DB::getInstance()->setBinding(var1, var2);
    }
    else if (binding == BindLTR)
    {
        DB::getInstance()->setBinding(var2, var1);
        auto value = DB::getInstance()->getSymbol(var2);
        DB::getInstance()->setSymbol(var1, value);
    }
    else
    {
        auto value = Parser::parseValue(var2);
        DB::getInstance()->setSymbol(var1, value);
    }
    return 0;
}
#endif