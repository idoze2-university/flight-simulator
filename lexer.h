#ifndef LEXER_H
#define LEXER_H
#define OPEN_DATA_SERVER_STR Command::OpenDataServerStr
#define CONNECT_CONTROL_CLIENT_STR Command::ConnectControlClientStr
#define VAR_STR "var"
#define PRINT_STR "Print"
#define SLEEP_STR "Sleep"
#define IF_STR "if"
#define WHILE_STR "while"
#define CLOSE_BRACKET_STR "}"
#define BUFFER_SIZE 1024
#include "command.h"
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

    static list<string> lex(std::string);
};

#endif