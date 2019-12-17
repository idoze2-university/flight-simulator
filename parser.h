#include <iostream>
class Parser
{
    FILE *fp;

public:
    Parser() {}
    Parser(FILE *fileptr) : fp(fileptr) {}
    ~Parser() {}
};