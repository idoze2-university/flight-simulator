#ifndef LEXER_MAIN_CPP
#define LEXER_MAIN_CPP
#include "lexer_main.h"
int main()
{
    FILE *fp = fopen("fly.txt", "r");
    if (fp == NULL)
    {
        throw "Error opening file fly.txt";
    }
    Lexer::lex(fp);
    fclose(fp);
}
#endif