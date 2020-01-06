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
    list<list<string>> lexer_list = Lexer::lex(fp);
    for (auto entry : lexer_list)
    {
        cout << "[";
        for (auto s : entry)
        {
            cout << s << ",";
        }
        cout << "]" << endl;
    }
    fclose(fp);
    return 0;
}
