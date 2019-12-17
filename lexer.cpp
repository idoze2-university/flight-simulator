#ifndef LEXER_CPP
#define LEXER_CPP
#include "lexer.h"
/*
list<list<string>> Lexer::lex(FILE *fp)
{
    run on fp and return the data,for example, if the file reads:
    "
    openDataServer(5400)\n
    connectControlClient("127.0.0.1",5402)\n
    var warp -> sim("/sim/time/warp")\n
    "
    we should return:
    [
        ["openDataServer","5400"],
        ["connectControlClient","127.0.0.1","5402"],
        ["var","warp","->","sim(\"/sim/time/warp\")"]
    ]
    later, we'll lex-parse this text.

}
*/
#endif