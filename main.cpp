#include "command.h"
#include "parser.h"
#include "lexer.h"

int main_old()
{
    // //------Open the file from argv[1]-----------------------------------------------------------//
    // FILE *fp;
    // if (argc > 1)
    //     fp = fopen(argv[1], "r");
    // else //Make sure an argument is provided.
    // {
    //     cerr << "Please provide a file name for commands file." << endl;
    // }
    //-----Run program from file-----------------------------------------------------------------//
    list<list<string>> data;
    //data = Lexer::lex(fp);
    list<string> open;
    open.push_back(Command::OpenDataServerStr);
    open.push_back("5400");
    data.push_back(open);
    auto program = Parser::parse(data);
    for (auto p : program)
    {
        auto comm = p.first;
        string *args = new string[p.second.size()];
        copy(p.second.begin(), p.second.end(), args);
        comm.execute(args);
    }
    //------Free Memory--------------------------------------------------------------------------//
    //fclose(fp);

    //TODO: complete writing command methods.
    return 1;
}