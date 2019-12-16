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
    //------Create Parser------------------------------------------------------------------------//
    Parser parser = Parser(fp);
    //------lex-Parse commands file--------------------------------------------------------------//
    map<const char *, Command> command_parser;
    command_parser.emplace(OpenDataServerStr, Command(openDataServer));
    command_parser.emplace(ConnectControlClientStr, Command(connectControlClient));
    command_parser.emplace(VarStr, Command(varcmd));
    command_parser.emplace(PrintStr, Command(printcmd));
    command_parser.emplace(SleepStr, Command(sleepcmd));
    command_parser.emplace(WhileStr, Command(whilecmd));
    //TODO: complete writing command methods.
    //------Free Memory--------------------------------------------------------------------------//
}

int openDataServer(string arg)
{
    int port = stoi(arg);
    port = port; //TO DO: Continue working on openDataServer.
    return 1;
}
