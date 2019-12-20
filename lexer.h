#ifndef LEXER_H
#define LEXER_H
class Command;
#include <iostream>
#include <list>
using namespace std;
//---Class Labels--------------------------------------------------------------------------------//
class Lexer;
//----Class Implementations----------------------------------------------------------------------//
class Lexer
{
public:
    static list<list<string>> lex(FILE *);
};
#endif