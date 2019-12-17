#ifndef PARSER_CPP
#define PARSER_CPP
#include "parser.h"
list<pair<Command, list<string>>> Parser::parse(list<list<string>> lexer_output)
{
    auto ret = list<pair<Command, list<string>>>();
    for (auto entry : lexer_output)
    {
        Command cmd(DB::getInstance()->getCommand(entry.front()));
        entry.pop_front();
        list<string> args = entry;
        ret.push_back(pair<Command, list<string>>(cmd, args));
    }
    return ret;
}
#endif