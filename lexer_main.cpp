#include "lexer_main.h"
int main()
{
    FILE *fp = fopen("fly.txt", "r");
    if (fp == nullptr)
    {
        throw "Error opening fly.txt";
    }
    list<list<string>> lexer_list = Lexer::lex(fp);
    fclose(fp);
    return 0;
}
