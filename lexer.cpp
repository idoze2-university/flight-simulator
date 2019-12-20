#ifndef LEXER_CPP
#define LEXER_CPP
#include "lexer.h"
list<list<string>> Lexer::lex(FILE *fp)
{
    std::string line;
    char buffer[100];
    list<list<string>> lexer_list;
    while (!feof(fp))
    {
        list<string> lexer_list_node;
        fgets(buffer, 100, fp);
        line = buffer;
        //line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.find("openDataServer") != string::npos)
        {
            std::string command, argument;
            command = line.substr(0, 14);
            int start_pos_arg = line.find("(") + 1, end_pos_arg = line.find(")") - 1;
            argument = line.substr(start_pos_arg, end_pos_arg);
            lexer_list_node.push_front(argument);
            lexer_list_node.push_front(command);
            lexer_list.push_back(lexer_list_node);
            for (auto i : lexer_list_node)
            {
                cout << i << endl;
            }
        }
        // else if (line.find(Command::ConnectControlClientStr)!=string::npos)
        // {
        //     std::string command,argument1,argument2;
        //     command = line.substr(0,Command::ConnectControlClientStr.length());
        //     int start_pos_arg1 = line.find("(")+1,end_pos_arg1=line.find(",")-1;
        //     int start_pos_arg2 = line.find(",")+1,end_pos_arg2=line.find(")")-1;
        //     argument1 = line.substr(start_pos_arg1,end_pos_arg1);
        //     argument2 = line.substr(start_pos_arg2,end_pos_arg2);
        //     lexer_list_node.push_front(argument2);
        //     lexer_list_node.push_front(argument1);
        //     lexer_list_node.push_front(command);
        //     lexer_list.push_back(lexer_list_node);
        // }
        // else if (line.find(Command::VarMethStr)!=string::npos)
        // {
        //     /* code */
        // }
        // else if (line.find(Command::PrintMethStr)!=string::npos)
        // {
        //     /* code */
        // }
        // else if (line.find(Command::SleepMethStr)!=string::npos)
        // {
        //     /* code */
        // }
        // else{

        // }
    }
}
#endif
