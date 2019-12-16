#include <string>
#include <map>
#include <iostream>
#include <thread>
using namespace std;

//----Command Strings----------------------------------------------------------------------------//
#define OpenDataServerStr "openDataServer"
#define ConnectControlClientStr "connectControlClient"
#define VarStr "var"
#define PrintStr "Print"
#define SleepStr "Sleep"
#define WhileStr "while"

//----Command Function Labels--------------------------------------------------------------------//
int openDataServer(string);
//int connectControlClient(string);
//TO DO: Continue working on lexer.

class Command
{
    int (*method)(string);

public:
    int execute(string arg) { return (method)(arg); };
    Command() {} // Default Ctor
    Command(int (*meth)(string)) : method(meth) {}
    ~Command() {}
};
