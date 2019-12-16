#include "command.h"

int main(int argc, char *argv[])
{
    //------Open the file from argv[1]-----------------------------------------------------------//
    FILE *fp;
    if (argc > 1)
        fp = fopen(argv[1], "r");
    else //Make sure an argument is provided.
    {
        cerr << "Please provide a file name for commands file." << endl;
        return 1;
    }
    //------lex-Parse commands file--------------------------------------------------------------//

    //TODO: complete writing command methods.
    //------Free Memory--------------------------------------------------------------------------//
}
map<const char *, Command> getCommandToStrMap()
{
    map<const char *, Command> cmdMap;
    cmdMap.emplace(OpenDataServerStr, Command(openDataServer));
    cmdMap.emplace(ConnectControlClientStr, Command(connectControlClient));
    cmdMap.emplace(VarStr, Command(varcmd));
    cmdMap.emplace(PrintStr, Command(printcmd));
    cmdMap.emplace(SleepStr, Command(sleepcmd));
    cmdMap.emplace(WhileStr, Command(whilecmd));
    return cmdMap;
}

int openDataServer(string arg)
{
    int port = stoi(arg);
    port = port; //TO DO: Continue working on openDataServer.
    return 1;
}
