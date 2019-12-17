#include "command.cpp"
#include "parser.h"

int main(int argc, char *argv[])
{
    map<const char *, pair<Command, int>> cmdMap = getCommandToStrMap();
    string args[] = {""};
    cmdMap[OpenDataServerStr].first.execute(args);
    //------Open the file from argv[1]-----------------------------------------------------------//
    FILE *fp;
    if (argc > 1)
        fp = fopen(argv[1], "r");
    else //Make sure an argument is provided.
    {
        cerr << "Please provide a file name for commands file." << endl;
        return 1;
    }
    Parser c = Parser(fp);
    fclose(fp);
    //error
    //------lex-Parse commands file--------------------------------------------------------------//

    //TODO: complete writing command methods.
    //------Free Memory--------------------------------------------------------------------------//
}