#pragma once
#include <string>
using namespace std;
class Menu
{
public:
    static const int MAX_COMMANDS = 20;

private:
    std::string* commands[MAX_COMMANDS];
    int nr_commands;
    const std::string prompt;

public:
    Menu(const std::string& prompt_);
    ~Menu(void);
    void Add_Command(const std::string& cmd);

    const std::string* Get_Command(void) const;
};

