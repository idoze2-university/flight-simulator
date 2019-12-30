#ifndef DB_H
#define DB_H
#include "command.h"
#include <unordered_map>
#include <memory>
#include <queue>
#include <mutex>
#include <regex>
using namespace std;
#define BUFFER_SIZE 1024
#define QUERY_SIZE 128
#define BindRTL "->"
#define BindLTR "<-"
#define BindEQ "="
typedef pair<string, double> updateEntry;
class DB
{
    DB();
    unordered_map<string, Command> _command_names;
    string names[36];
    unordered_map<string, double> _server_values;
    unordered_map<string, double> _symbol_table;
    unordered_map<string, string> _symbol_binding;
    queue<updateEntry> _update_queue;
    void enqueueUpdate(string, double);
    bool isBound(string);
    mutex global_lock;

public:
    static std::shared_ptr<DB> getInstance()
    {
        while (true)
        {
            try
            {
                static std::shared_ptr<DB> s{new DB};
                return s;
            }
            catch (const std::exception &e)
            {
            }
        }
    }
    //-- Mutex
    void lockMutex();
    void unlockMutex();

    //-- Getters
    Command getCommand(string);
    double getServerValue(string);
    double getSymbol(string);
    string getBinding(string);
    string getNextUpdateQuery();

    //-- Setters
    void setSymbol(string, double);
    void setBinding(string, string);
    void setServerValues(char *);
};

#endif