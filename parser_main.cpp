#include "parser.h"
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
    }
    auto prog = Parser::parse(Lexer::lex(fp));
    for (auto entry : prog)
    {
        cout << "[";
        for (auto s : entry.second)
        {
            cout << s << " ";
        }
        cout << "]" << endl;
    }
    fclose(fp);
    return 0;
}
