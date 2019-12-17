#include <string>
#include <map>
#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
//---Class Labels--------------------------------------------------------------------------------//
class Command;
//----Definitions--------------------------------------------------------------------------------//
#define DEF_PORT 5400
#define DEF_IP_ADDR "127.0.0.1"
//----Command Strings----------------------------------------------------------------------------//
#define OpenDataServerStr "openDataServer"
#define ConnectControlClientStr "connectControlClient"
#define VarMethStr "var"
#define PrintMethStr "Print"
#define SleepMethStr "Sleep"
#define WhileMethStr "while"
//-----Command Argument Count--------------------------------------------------------------------//
#define ARGC_OpenDataServer 1
#define ARGC_ConnectControlClient 0
//----Global Vars--------------------------------------------------------------------------------//

//----Assisting Functions------------------------------------------------------------------------//
map<const char *, pair<Command, int>> getCommandToStrMap();
void serverListen(int, int);
//----Command Function Labels--------------------------------------------------------------------//
int OpenDataServer(string[]);
int ConnectControlClient(string[]);
int VarMeth(string[]);
int PrintMeth(string[]);
int SleepMeth(string[]);
int WhileMeth(string[]);
//----Class Implementations----------------------------------------------------------------------//
class Command
{
    int (*method)(string[]);

public:
    int execute(string args[]) { return (method)(args); };
    Command() {} // Default Ctor
    Command(int (*meth)(string[])) : method(meth) {}
    ~Command() {}
};
