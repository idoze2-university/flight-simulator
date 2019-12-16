#include <string>
#include <map>
#include "iostream"
using namespace std;

//Command Strings

#define OpenDataServerStr "openDataServer"

//Command Function Labels

//Command *getCommands(char *);
int openDataServer(string);

class Command
{
    int (*method)(string);

public:
    int execute(string arg) { return (method)(arg); };
    Command() {}
    Command(int (*meth)(string)) : method(meth) {}
    ~Command() {}
};