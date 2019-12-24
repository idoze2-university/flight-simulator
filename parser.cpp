#ifndef PARSER_CPP
#define PARSER_CPP
#include "parser.h"
list<pair<Command, list<string>>> Parser::parse(list<list<string>> lexer_output)
{
    int inWhile = 0;
    auto ret = list<pair<Command, list<string>>>();
    for (auto entry : lexer_output)
    {
        if (entry.size() == 0)
        {
            inWhile = 0;
        }
        else
        {
            auto _command_name = entry.front();
            if (_command_name == Command::WhileMethStr)
            {
                entry.pop_front();
                inWhile = 1;
                list<string> args;
                args.push_back(entry.front());
                auto cmd = DB::getInstance()->getCommand(_command_name);
                ret.push_back(pair<Command, list<string>>(cmd, args));
            }
            else if (inWhile)
            {
                auto while_command = ret.back().first;
                auto while_args = ret.back().second;
                ret.pop_back();
                string stringer = "";
                while (!entry.empty())
                {
                    stringer += entry.front();
                    entry.pop_front();
                    if (!entry.empty())
                        stringer += ",";
                }
                while_args.push_back(stringer);
                ret.push_back(pair<Command, list<string>>(while_command, while_args));
            }
            else
            {
                ret.push_back(parse_line(entry));
            }
        }
    }
    return ret;
}

pair<Command, list<string>> Parser::parse_line(list<string> lexer_output_line)
{
    Command cmd;
    auto _command_name = lexer_output_line.front();
    try
    {
        cmd = Command(DB::getInstance()->getCommand(_command_name));
        lexer_output_line.pop_front();
    }
    catch (const char *e)
    {
        cmd = Command(Command::DefineVar);
    }
    list<string> args = lexer_output_line;
    return pair<Command, list<string>>(cmd, args);
}
#endif