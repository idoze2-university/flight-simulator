#ifndef PARSER_CPP
#define PARSER_CPP
#include "parser.h"
list<pair<Command, list<string>>> Parser::parse(list<list<string>> lexer_output)
{
    Command cmd;
    auto ret = list<pair<Command, list<string>>>();
    for (auto entry : lexer_output)
    {
        auto _command_name = entry.front();
        try
        {
            cmd = Command(DB::getInstance()->getCommand(_command_name));
            entry.pop_front();
        }
        catch (const std::exception &e)
        {
            cmd = Command(Command::DefineVar);
        }
        list<string> args = entry;
        ret.push_back(pair<Command, list<string>>(cmd, args));
    }
    return ret;
}

double Parser::parseValue(string expression)
{
    try
    {
        return stoi(expression);
    }
    catch (const std::exception &e)
    {
        cout << "Cannot evaluate \'" << expression << "\'" << endl;
        return 0;
    }
}
#endif