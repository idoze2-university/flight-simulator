#ifndef WHILE_COMMAND_CPP
#define WHILE_COMMAND_CPP
#include "../parser.h"
#include "../command.h"
int Command::WhileMeth(string args[])
{
    while (Parser::parseCondition(args[0]))
    {
        int i = 0;
        while (1)
        {
            try
            {
                string s = args[++i];
                list<string> cmd;
                std::string delimiter = ",";
                size_t pos = 0;
                std::string token;
                while ((pos = s.find(delimiter)) != std::string::npos)
                {
                    token = s.substr(0, pos);
                    cmd.push_back(token);
                    s.erase(0, pos + delimiter.length());
                }
                auto p = Parser::parse_line(cmd);
                auto comm = p.first;
                string *arg_array = new string[p.second.size()];
                copy(p.second.begin(), p.second.end(), arg_array);
                comm.execute(arg_array);
            }
            catch (const std::exception &e)
            {
                break;
            }
        }
    }
    return 0;
}
#endif