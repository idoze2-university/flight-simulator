#include "../command.h"
#include "../lexer.h"
#include "../parser.h"

int main(int argc, char *argv[])
{
    //------Open the file from argv[1]-----------------------------------------------------------//
    FILE *fp;
    if (argc > 1)
        fp = fopen(argv[1], "r");
    else //Make sure an argument is provided.
    {
        cerr << "Please provide a file name for commands file." << endl;
    }
    //-----Run program from file-----------------------------------------------------------------//
    auto program = Parser::parse(Lexer::lex(fp));
    for (auto p : program)
    {
        auto comm = p.first;
        string *args = new string[p.second.size()];
        copy(p.second.begin(), p.second.end(), args);
        comm.execute(args);
    }
    //------Free Memory--------------------------------------------------------------------------//
    fclose(fp);

    //TODO: complete writing command methods.
    return 0;
}