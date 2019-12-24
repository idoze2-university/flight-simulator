#ifndef PARSER_CPP
#define PARSER_CPP
#include "parser.h"
list<pair<Command, list<string>>> Parser::parse(list<list<string>> lexer_output)
{
    int inScope = 0;
    auto ret = list<pair<Command, list<string>>>();
    for (auto entry : lexer_output)
    {
        auto _command_name = entry.front();
        if (_command_name == CLOSE_BRACKET_STR)
        {
            entry.pop_front();
            auto scope_command = ret.back().first;
            auto scope_args = ret.back().second;
            ret.pop_back();
            scope_args.push_front(entry.front());
            ret.push_back(pair<Command, list<string>>(scope_command, scope_args));
            inScope = 0;
        }
        else
        {
            if (_command_name == Command::WhileMethStr || _command_name == Command::IfMethStr)
            {
                entry.pop_front();
                inScope = 1;
                list<string> args;
                args.push_back(entry.front());
                auto cmd = DB::getInstance()->getCommand(_command_name);
                ret.push_back(pair<Command, list<string>>(cmd, args));
            }
            else if (inScope)
            {
                auto scope_command = ret.back().first;
                auto scope_args = ret.back().second;
                ret.pop_back();
                string stringer = "";
                while (!entry.empty())
                {
                    stringer += entry.front();
                    entry.pop_front();
                    stringer += ",";
                }
                scope_args.push_back(stringer);
                ret.push_back(pair<Command, list<string>>(scope_command, scope_args));
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