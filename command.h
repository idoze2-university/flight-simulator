#include <string>
#include <map>
#include <iostream>
#include <thread>
using namespace std;
//---Class Labels--------------------------------------------------------------------------------//
class Parser;
class Command;
//----Command Strings----------------------------------------------------------------------------//
#define OpenDataServerStr "openDataServer"
#define ConnectControlClientStr "connectControlClient"
#define VarStr "var"
#define PrintStr "Print"
#define SleepStr "Sleep"
#define WhileStr "while"
//----Assisting Functions------------------------------------------------------------------------//
//----Command Function Labels--------------------------------------------------------------------//
int openDataServer(string);
int connectControlClient(string);
int varcmd(string);
int printcmd(string);
int sleepcmd(string);
int whilecmd(string);
//int connectControlClient(string);
//TO DO: Continue working on parser.
//----Class Implementations----------------------------------------------------------------------//
class Parser
{
    FILE *fp;

public:
    Parser() {}
    Parser(FILE *fileptr) : fp(fileptr) {}
    ~Parser() {}
};

class Command
{
    int (*method)(string);

public:
    int execute(string arg) { return (method)(arg); };
    Command() {} // Default Ctor
    Command(int (*meth)(string)) : method(meth) {}
    ~Command() {}
};
