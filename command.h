#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <map>
#include <memory>
#include <iostream>
using namespace std;
//---Class Labels--------------------------------------------------------------------------------//
class Command;
//----Definitions--------------------------------------------------------------------------------//
#define DEF_PORT 5400
//Command Strings
//Command Argument Count
#define ARGC_OpenDataServer 1       //Port
#define ARGC_ConnectControlClient 2 //IP,Port
#define ARGC_VarMeth 2              //Hook direction (->/<-),Value
#define ARGC_PrintMeth 1            //Data
#define ARGC_SleepMeth 1            //Time
#define ARGC_While 0                //Condition+function(could be anything)
//----Global Vars--------------------------------------------------------------------------------//

//----Static Function Labels---------------------------------------------------------------------//
//Assisting Functions
void serverListen(int, int);
//Command Function Labels
//----Class Implementations----------------------------------------------------------------------//
class Command
{
    int (*method)(string[]);

public:
    Command() {} // Default Ctor, not used.
    //--Consts
    static const string OpenDataServerStr;
    static const string ConnectControlClientStr;
    static const string VarMethStr;
    static const string PrintMethStr;
    static const string SleepMethStr;
    static const string WhileMethStr;
    static const string IfMethStr;
    //--Method labels
    static int OpenDataServer(string[]);
    static int ConnectControlClient(string[]);
    static int DefineVar(string[]);
    static int PrintMeth(string[]);
    static int SleepMeth(string[]);
    static int WhileMeth(string[]);
    // static int IfMeth(string[]);
    int execute(string args[]) { return (method)(args); };
    Command(int (*meth)(string[])) : method(meth) {}
    ~Command() {}
};
#endif