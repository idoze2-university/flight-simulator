#include "lexer.h"

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
    if (fp == NULL) //Make sure file has opened.
    {
        cerr << "Cannot open commands file,\nPlease verify the name." << endl;
        return 1;
    }
    //------lex-Parse commands file--------------------------------------------------------------//
    map<const char *, Command> command_parser;
    command_parser.emplace(OpenDataServerStr, Command(openDataServer));
    //TO DO: Add all possible commands to command_parser
    //-------
}

int openDataServer(string arg)
{
    int port = stoi(arg);
    port = port;//TO DO: Continue working on openDataServer.
    return 1;
}
