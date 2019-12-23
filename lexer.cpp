#include "lexer.h"

bool isLowerChar(char c)
{
    //a-z
    if (c >= 97 && c <= 122)
    {
        return true;
    }
    return false;
}

bool isUpperChar(char c)
{
    //A-Z
    if (c >= 65 && c <= 90)
    {
        return true;
    }
    return false;
}

bool isDigit(char c)
{
    //0-9
    if (c >= 48 && c <= 57)
    {
        return true;
    }
    return false;
}

bool Lexer::isMathToken(char c)
{
    switch (c)
    {
    case '+':
        return true;
    case '-':
        return true;
    case '*':
        return true;
    case '/':
        return true;
    case '(':
        return true;
    case ')':
        return true;
    case '.':
        return true;
    default:
        return false;
    }
}

bool Lexer::isBadCharacter(char c, int status)
{
    switch (status)
    {
    case 0:
        if (c == ' ' || c == '\t' || c == '\b' || c == '\n')
        {
            return true;
        }
        break;
    case 1:
        if (!(isLowerChar(c)) && !(isUpperChar(c)) && !(isDigit(c)) && c != '_')
        {
            return true;
        }
        break;
    case 2:
        if (!(isLowerChar(c)) && !(isUpperChar(c)) && !(isDigit(c)) && c != '_')
        {
            if (!isMathToken(c))
            {
                return true;
            }
        }
        break;
    default:
        return false;
    }
    return false;
}

std::string strip(std::string line)
{
    bool s_flag = false;
    std::string s = "";
    for (char c : line)
    {
        if (Lexer::isBadCharacter(c, 0) && !s_flag)
        {
            continue;
        }
        else if (c == '"' && !s_flag)
        {
            s_flag = true;
        }
        else if (c == '"')
        {
            s_flag = false;
        }
        s += c;
    }
    return s;
}

void openDataServer_bad_line(std::string line)
{
    //@__Garbage__@openDataServer()
    string e = "openDataServer Command Error";
    if (line.find("openDataServer") != 0)
    {
        throw e;
    }
    //openDataServer@__Garbage__@()
    else if (line.find("(") != 14)
    {
        throw e;
    }
    //openDataServer()@__Garbage__@
    else if (line[line.size() - 1] != ')')
    {
        throw e;
    }
}

void connectControlClient_bad_line(std::string line)
{
    //@__Garbage__@connectControlClient()
    string e = "connectControlClient Command Error";
    if (line.find("connectControlClient") != 0)
    {
        throw e;
    }
    //connectControlClient@__Garbage__@()
    else if (line.find("(") != 20)
    {
        throw e;
    }
    //connectControlClient()@__Garbage__@
    else if (line[line.size() - 1] != ')')
    {
        throw e;
        //connectControlClient(arg1 __no,__arg2)
    }
    else if (line.find(",") == string::npos)
    {
        throw e;
    }
}

void var_bad_line(std::string line)
{
    string e = "var Command Error";
    bool badOperator_flag = true;
    //@__Garbage__@var_Name_Operator_Argument
    if (line.find("var") != 0)
    {
        throw e;
    }
    //
    if (line.find("<-") != string::npos)
    {
        badOperator_flag = false;
        char c;
        //bad Name
        unsigned int i = 3, pos = line.find("<-");
        for (; i < pos; i++)
        {
            c = line[i];
            if (Lexer::isBadCharacter(c, 1))
            {
                throw e;
            }
        }
        if (i == 3)
        {
            throw e;
        }
        //bad Argument
        string argument = line.substr(pos + 2, line.size());
        if (argument.find("sim") != 0)
        {
            throw e;
        }
        if (argument.find("(") != 3)
        {
            throw e;
        }
        if (argument[argument.size() - 1] != ')')
        {
            throw e;
        }
    }
    else if (line.find("->") != string::npos)
    {
        badOperator_flag = false;
        char c;
        unsigned int i = 3, pos = line.find("->");
        //bad Name
        for (; i < pos; i++)
        {
            c = line[i];
            if (Lexer::isBadCharacter(c, 1))
            {
                throw e;
            }
        }
        if (i == 3)
        {
            throw e;
        }
        //bad Argument
        string argument = line.substr(pos + 2, line.size());
        if (argument.find("sim") != 0)
        {
            throw e;
        }
        if (argument.find("(") != 3)
        {
            throw e;
        }
        if (argument[argument.size() - 1] != ')')
        {
            throw e;
        }
    }
    else if (line.find("=") != string::npos)
    {
        badOperator_flag = false;
        char c;
        unsigned int i = 3, pos = line.find("=");
        //bad Name
        for (; i < pos; i++)
        {
            c = line[i];
            if (Lexer::isBadCharacter(c, 1))
            {
                throw e;
            }
        }
        if (i == 3)
        {
            throw e;
        }
        //bad Argument
        string argument = line.substr(pos + 1, line.size());
        for (char ch : argument)
        {
            if (Lexer::isBadCharacter(ch, 1))
            {
                throw e;
            }
        }
    }
    if (badOperator_flag)
    {
        throw e;
    }
}

void print_bad_line(std::string line)
{
    string e = "Print Command Error";
    //@__Garbage__@Print()
    if (line.find("Print") != 0)
    {
        throw e;
    }
    //Print@__Garbage__@()
    else if (line.find("(") != 5)
    {
        throw e;
    }
    //Print()@__Garbage__@
    else if (line[line.size() - 1] != ')')
    {
        throw e;
    }
}

void sleep_bad_line(std::string line)
{
    string e = "Sleep Command Error";
    //@__Garbage__@Sleep()
    if (line.find("Sleep") != 0)
    {
        throw e;
    }
    //Sleep@__Garbage__@()
    else if (line.find("(") != 5)
    {
        throw e;
    }
    //Sleep()@__Garbage__@
    else if (line[line.size() - 1] != ')')
    {
        throw e;
    }
}

void if_bad_line(std::string line)
{
    string e = "if Condition Bad Command";
    //@__Garbage__@if_condition{
    if (line.find("if") != 0)
    {
        throw e;
    }
    //if_condition{@__Garbage__@
    else if (line[line.size() - 1] != '{')
    {
        throw e;
    }
    else if (line.size() == 3)
    {
        throw e;
    }
}

void while_bad_line(std::string line)
{
    string e = "while Condition Bad Command";
    //@__Garbage__@while_condition{
    if (line.find("while") != 0)
    {
        throw e;
    }
    //while{@__Garbage__@
    else if (line[line.size() - 1] != '{')
    {
        throw e;
    }
    else if (line.size() == 6)
    {
        throw e;
    }
}

void closeCondition_bad_line(std::string line)
{
    string e = "Bad closing Condition, unvalid '}'";
    if (line.size() != 1)
    {
        throw e;
    }
}

void unknownCommand_bad_line(bool flag)
{
    string e = "Unrecognized Command Error";
    flag ? throw e : 0;
}

void printError(std::string e, int line_counter)
{
    cout << e + " in line " + std::to_string(line_counter) + "\n";
}

list<list<string>> Lexer::lex(FILE *fp)
{
    std::string line;
    char buffer[BUFFER_SIZE];
    int pos, line_counter = 0;
    list<list<string>> lexer_list;
    while (!feof(fp))
    {
        line_counter++;
        bool unvalidC_flag = true;
        list<string> lexer_list_node;
        fgets(buffer, BUFFER_SIZE, fp);
        line = strip(buffer);
        if (line == "")
        {
            unvalidC_flag = false;
        }
        else if (line.find(OPEN_DATA_SERVER_STR) != string::npos)
        {
            unvalidC_flag = false;
            try
            {
                openDataServer_bad_line(line);
            }
            catch (string e)
            {
                printError(e, line_counter);
            }
            std::string command, argument;
            pos = line.size();
            command = line.substr(0, 14);
            argument = line.substr(15, pos - 16);
            lexer_list_node.push_back(command);
            lexer_list_node.push_back(argument);
            lexer_list.push_back(lexer_list_node);
        }
        else if (line.find(CONNECT_CONTROL_CLIENT_STR) != string::npos)
        {
            unvalidC_flag = false;
            try
            {
                connectControlClient_bad_line(line);
            }
            catch (string e)
            {
                printError(e, line_counter);
            }
            std::string command, argument1, argument2;
            command = line.substr(0, 20);
            pos = line.find(",");
            int end_pos_arg1 = pos - 1;
            int start_pos_arg2 = pos + 1, end_pos_arg2 = line.size();
            argument1 = line.substr(22, end_pos_arg1 - 22);
            argument2 = line.substr(start_pos_arg2, end_pos_arg2 - start_pos_arg2 - 1);
            lexer_list_node.push_back(command);
            lexer_list_node.push_back(argument1);
            lexer_list_node.push_back(argument2);
            lexer_list.push_back(lexer_list_node);
        }
        else if (line.find(VAR_STR) != string::npos)
        {
            unvalidC_flag = false;
            try
            {
                var_bad_line(line);
            }
            catch (string e)
            {
                printError(e, line_counter);
            }
            std::string command, name, operation, argument;
            bool assign_to_src, assign_to_dest;
            line.find("<-") != string::npos ? assign_to_src = true : assign_to_src = false;
            line.find("->") != string::npos ? assign_to_dest = true : assign_to_dest = false;
            command = line.substr(0, 3);
            if (assign_to_dest)
            {
                pos = line.find("-");
                name = line.substr(3, pos - 3);
                operation = "->";
                argument = line.substr(pos + 2, line.size());
            }
            else if (assign_to_src)
            {
                pos = line.find("<");
                name = line.substr(3, pos - 3);
                operation = "<-";
                argument = line.substr(pos + 2, line.size());
            }
            else
            {
                pos = line.find("=");
                name = line.substr(3, pos - 3);
                operation = "=";
                argument = line.substr(pos + 1, line.size());
            }
            lexer_list_node.push_back(command);
            lexer_list_node.push_back(name);
            lexer_list_node.push_back(operation);
            lexer_list_node.push_back(argument);
            lexer_list.push_back(lexer_list_node);
        }
        else if (line.find(PRINT_STR) != string::npos)
        {
            try
            {
                print_bad_line(line);
            }
            catch (string e)
            {
                printError(e, line_counter);
            }
            unvalidC_flag = false;
            std::string command, argument;
            command = line.substr(0, 5);
            argument = line.substr(6, line.size() - 7);
            lexer_list_node.push_back(command);
            lexer_list_node.push_back(argument);
            lexer_list.push_back(lexer_list_node);
        }
        else if (line.find(SLEEP_STR) != string::npos)
        {
            try
            {
                sleep_bad_line(line);
            }
            catch (string e)
            {
                printError(e, line_counter);
            }
            unvalidC_flag = false;
            std::string command, argument;
            command = line.substr(0, 5);
            argument = line.substr(6, line.size() - 7);
            lexer_list_node.push_back(command);
            lexer_list_node.push_back(argument);
            lexer_list.push_back(lexer_list_node);
        }
        else if (line.find(IF_STR) != string::npos)
        {
            try
            {
                if_bad_line(line);
            }
            catch (string e)
            {
                printError(e, line_counter);
            }
            unvalidC_flag = false;
            std::string command, condition, has_bracet_flag = "0", go_forward = "0";
            command = "if";
            condition = line.substr(2, line.size() - 3);
            lexer_list_node.push_back(command);
            lexer_list_node.push_back(condition);
            lexer_list_node.push_back(has_bracet_flag);
            lexer_list_node.push_back(go_forward);
            lexer_list.push_back(lexer_list_node);
        }
        else if (line.find(WHILE_STR) != string::npos)
        {
            try
            {
                while_bad_line(line);
            }
            catch (string e)
            {
                printError(e, line_counter);
            }
            unvalidC_flag = false;
            std::string command, condition, has_bracet_flag = "0", go_forward = "0";
            command = "while";
            condition = line.substr(5, line.size() - 6);
            lexer_list_node.push_back(command);
            lexer_list_node.push_back(condition);
            lexer_list_node.push_back(has_bracet_flag);
            lexer_list_node.push_back(go_forward);
            lexer_list.push_back(lexer_list_node);
        }
        else if (line.find(CLOSE_BRACKET_STR) != string::npos)
        {
            try
            {
                closeCondition_bad_line(line);
            }
            catch (string e)
            {
                printError(e, line_counter);
            }
            unvalidC_flag = false;
            int move_counter = 0;
            bool condition_found = false;
            std::string closing;
            auto it = --lexer_list.end();
            try
            {
                std::string e = "Bad '}'";
                while ((it != --lexer_list.begin()) && !condition_found)
                {
                    move_counter++;
                    auto node = *it;
                    auto node_it = node.begin();
                    if (*node_it == "if" || *node_it == "while")
                    {
                        auto s = *node_it;
                        std::advance(node_it, 2);
                        if (*node_it == "0")
                        {
                            closing = s;
                            *node_it = "1";
                            node_it++;
                            *node_it = std::to_string(move_counter + 1);
                            *it = node;
                            condition_found = true;
                        }
                    }
                    --it;
                }
                if (!condition_found)
                {
                    throw e;
                }
            }
            catch (std::string e)
            {
                printError(e, line_counter);
            }
            std::string command = "}", go_back = std::to_string(move_counter);
            lexer_list_node.push_back(command);
            lexer_list_node.push_back(closing);
            lexer_list_node.push_back(go_back);
            lexer_list.push_back(lexer_list_node);
        }
        else if (line.find("=") != string::npos)
        {
            unvalidC_flag = false;
            std::string src, dest;
            pos = line.find("=");
            dest = line.substr(0, pos);
            src = line.substr(pos + 1, line.size());
            try
            {
                std::string e = "Bad assigning";
                for (char c : dest)
                {
                    if (Lexer::isBadCharacter(c, 2))
                    {
                        throw e;
                    }
                }
                for (char c : src)
                {
                    if (Lexer::isBadCharacter(c, 2))
                    {
                        throw e;
                    }
                }
            }
            catch (std::string e)
            {
                printError(e, line_counter);
            }
            lexer_list_node.push_back(dest);
            lexer_list_node.push_back(src);
            lexer_list.push_back(lexer_list_node);
        }
        try
        {
            unknownCommand_bad_line(unvalidC_flag);
        }
        catch (string e)
        {
            printError(e, line_counter);
        }
    }
    return lexer_list;
}

list<string> Lexer::lex(std::string s)
{
    int pos;
    int line_counter = 0;
    bool unvalidC_flag = true;
    list<string> lexer_list_node;
    std::string line = strip(s);
    if (line == "")
    {
        unvalidC_flag = false;
    }
    else if (line.find(OPEN_DATA_SERVER_STR) != string::npos)
    {
        unvalidC_flag = false;
        try
        {
            openDataServer_bad_line(line);
        }
        catch (string e)
        {
            printError(e, line_counter);
        }
        std::string command, argument;
        pos = line.size();
        command = line.substr(0, 14);
        argument = line.substr(15, pos - 16);
        lexer_list_node.push_back(command);
        lexer_list_node.push_back(argument);
    }
    else if (line.find(CONNECT_CONTROL_CLIENT_STR) != string::npos)
    {
        unvalidC_flag = false;
        try
        {
            connectControlClient_bad_line(line);
        }
        catch (string e)
        {
            printError(e, line_counter);
        }
        std::string command, argument1, argument2;
        command = line.substr(0, 20);
        pos = line.find(",");
        int end_pos_arg1 = pos - 1;
        int start_pos_arg2 = pos + 1, end_pos_arg2 = line.size();
        argument1 = line.substr(22, end_pos_arg1 - 22);
        argument2 = line.substr(start_pos_arg2, end_pos_arg2 - start_pos_arg2 - 1);
        lexer_list_node.push_back(command);
        lexer_list_node.push_back(argument1);
    }
    else if (line.find(VAR_STR) != string::npos)
    {
        unvalidC_flag = false;
        try
        {
            var_bad_line(line);
        }
        catch (string e)
        {
            printError(e, line_counter);
        }
        std::string command, name, operation, argument;
        bool assign_to_src, assign_to_dest;
        line.find("<-") != string::npos ? assign_to_src = true : assign_to_src = false;
        line.find("->") != string::npos ? assign_to_dest = true : assign_to_dest = false;
        command = line.substr(0, 3);
        if (assign_to_dest)
        {
            pos = line.find("-");
            name = line.substr(3, pos - 3);
            operation = "->";
            argument = line.substr(pos + 2, line.size());
        }
        else if (assign_to_src)
        {
            pos = line.find("<");
            name = line.substr(3, pos - 3);
            operation = "<-";
            argument = line.substr(pos + 2, line.size());
        }
        else
        {
            pos = line.find("=");
            name = line.substr(3, pos - 3);
            operation = "=";
            argument = line.substr(pos + 1, line.size());
        }
        lexer_list_node.push_back(command);
        lexer_list_node.push_back(name);
        lexer_list_node.push_back(operation);
        lexer_list_node.push_back(argument);
    }
    else if (line.find(PRINT_STR) != string::npos)
    {
        try
        {
            print_bad_line(line);
        }
        catch (string e)
        {
            printError(e, line_counter);
        }
        unvalidC_flag = false;
        std::string command, argument;
        command = line.substr(0, 5);
        argument = line.substr(6, line.size() - 7);
        lexer_list_node.push_back(command);
        lexer_list_node.push_back(argument);
    }
    else if (line.find(SLEEP_STR) != string::npos)
    {
        try
        {
            sleep_bad_line(line);
        }
        catch (string e)
        {
            printError(e, line_counter);
        }
        unvalidC_flag = false;
        std::string command, argument;
        command = line.substr(0, 5);
        argument = line.substr(6, line.size() - 7);
        lexer_list_node.push_back(command);
        lexer_list_node.push_back(argument);
    }
    else if (line.find(IF_STR) != string::npos)
    {
        try
        {
            if_bad_line(line);
        }
        catch (string e)
        {
            printError(e, line_counter);
        }
        unvalidC_flag = false;
        std::string command, condition, has_bracet_flag = "0", go_forward = "0";
        command = "if";
        condition = line.substr(2, line.size() - 3);
        lexer_list_node.push_back(command);
        lexer_list_node.push_back(condition);
        lexer_list_node.push_back(has_bracet_flag);
        lexer_list_node.push_back(go_forward);
    }
    else if (line.find(WHILE_STR) != string::npos)
    {
        try
        {
            while_bad_line(line);
        }
        catch (string e)
        {
            printError(e, line_counter);
        }
        unvalidC_flag = false;
        std::string command, condition, has_bracet_flag = "0", go_forward = "0";
        command = "while";
        condition = line.substr(5, line.size() - 6);
        lexer_list_node.push_back(command);
        lexer_list_node.push_back(condition);
        lexer_list_node.push_back(has_bracet_flag);
        lexer_list_node.push_back(go_forward);
    }
    else if (line.find("=") != string::npos)
    {
        unvalidC_flag = false;
        std::string src, dest;
        pos = line.find("=");
        dest = line.substr(0, pos);
        src = line.substr(pos + 1, line.size());
        try
        {
            std::string e = "Bad assigning";
            for (char c : dest)
            {
                if (Lexer::isBadCharacter(c, 2))
                {
                    throw e;
                }
            }
            for (char c : src)
            {
                if (Lexer::isBadCharacter(c, 2))
                {
                    throw e;
                }
            }
        }
        catch (std::string e)
        {
            printError(e, line_counter);
        }
        lexer_list_node.push_back(dest);
        lexer_list_node.push_back(src);
    }
    try
    {
        unknownCommand_bad_line(unvalidC_flag);
    }
    catch (string e)
    {
        printError(e, line_counter);
    }
    return lexer_list_node;
}