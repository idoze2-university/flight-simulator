#ifndef LEXER_CPP
#define LEXER_CPP

#include "lexer.h"

list <list<string>> Lexer::lex(FILE *fp) {
    std::string line = "", s ;
    char buffer[1024];
    list <list<string>> lexer_list;
    while (!feof(fp)) {
        list <string> lexer_list_node;
        fgets(buffer, 1024, fp);
        line = buffer;
//        bool s_flag = false;
//        for (char c: s) {
//            if (c == ' ' && !s_flag) {
//                continue;
//            } else if (c == '"' && !s_flag) {
//                s_flag = true;
//            } else if (c == '"' && s_flag) {
//                s_flag = false;
//                continue;
//            }
//            line += c;
//        }
        if (line.find("openDataServer") != string::npos) {
            std::string command, argument;
            command = line.substr(0, 14);
            argument = line.substr(15, 4);
            lexer_list_node.push_back(command);
            lexer_list_node.push_back(argument);
            lexer_list.push_back(lexer_list_node);
        } else if (line.find("connectControlClient") != string::npos) {
            std::string command, argument1, argument2;
            command = line.substr(0, 20);
            int end_pos_arg1 = line.find(",") - 1;
            int start_pos_arg2 = line.find(",") + 1, end_pos_arg2 = line.find(")");
            argument1 = line.substr(22, end_pos_arg1 - 22);
            argument2 = line.substr(start_pos_arg2, end_pos_arg2 - start_pos_arg2);
            lexer_list_node.push_back(command);
            lexer_list_node.push_back(argument1);
            lexer_list_node.push_back(argument2);
            lexer_list.push_back(lexer_list_node);
        }
//         else if (line.find(Command::VarMethStr)!=string::npos)
//         {
//             /* code */
//         }
        else if (line.find("Print") != string::npos) {
            std::string command, argument;
            command = line.substr(0, 5);
            if (line[6] == '"') {
                argument = line.substr(7, line.find(")") - 8);
            } else {
                argument = line.substr(6, line.find(")") - 6);
            }
        }
//         else if (line.find(Command::SleepMethStr)!=string::npos)
//         {
//             /* code */
//         }
//         else{
//
//         }
    }
    return lexer_list;
}

//std::string removeSpaces(string line) {
//    string s = "";
//    bool s_flag = false;
//    for (char c: line) {
//        if (c == ' ' && !s_flag) {
//            continue;
//        } else if (c == '"' && !s_flag) {
//            s_flag = true;
//        } else if (c == '"' && s_flag) {
//            s_flag = false;
//            continue;
//        }
//        s += c;
//    }
//    return s;
//}

#endif
