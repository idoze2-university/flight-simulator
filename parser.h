#ifndef PARSER_H
#define PARSER_H
#include <list>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include "lexer.h"
#include "command.h"
#include "DB.h"
using namespace std;
class Parser
{
public:
    static list<pair<Command, list<string>>> parse(list<list<string>>);
    static double parseValue(string);
};
#endif