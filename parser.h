#include <iostream>
#include "command.h"

class Parser
{
    FILE *fp;

public:
    Parser() {}
    Parser(FILE *fileptr) : fp(fileptr) {}
    ~Parser() {}
};