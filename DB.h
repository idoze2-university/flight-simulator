#ifndef DB_H
#define DB_H
#include "command.h"
#include <unordered_map>
#include <memory>
#include <mutex>
using namespace std;
class DB
{
    DB();
    unordered_map<string, Command> _command_names;
    unordered_map<string, double> _server_values;
    // unordered_map<string, string> _symbol_binding;
    // unordered_map<string, double> _symbol_table;
    mutex global_lock;

public:
    // DB(DB const &) = delete;
    // void operator=(DB const &) = delete;
    static std::shared_ptr<DB> getInstance()
    {
        static std::shared_ptr<DB> s{new DB};
        return s;
    }
    void lockMutex();
    void unlockMutex();
    Command getCommand(string);
    double getServerValue(string);
};

#endif