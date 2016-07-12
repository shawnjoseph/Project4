#include <iostream>
#include <string>
#include <cassert>
#include "Menu.h"
using namespace std;

Menu::Menu(const string& prompt_) :
        nr_commands(0), prompt(prompt_)
{}
Menu::~Menu(void)
{
    for (int i = 0; i < nr_commands; ++i)
    {
        delete commands[i];
    }
}

void Menu::Add_Command(const string& cmd)
{
    assert(nr_commands < MAX_COMMANDS);
    commands[nr_commands++] = new string(cmd);
}

const string* Menu::Get_Command(void) const
{
    string cmd;
    int choice = 0;
    while (true)
    {
        cout << prompt << endl;
        for (int i = 0; i < nr_commands; ++i)
        {
            cout << (i + 1) << ": " << *commands[i] << endl;
        }
        cout << endl;
        cout << "> ";
        getline(cin, cmd);
        try
        {
            choice = stoi(cmd);
        }
        catch (exception ex)
        {
            choice = 0;
        }

        if ((choice < 1) || (choice > nr_commands))
        {
            cout << "Invalid choice\n";
            cout << "Please try again\n\n";
            continue;
        }
        return commands[--choice];
    }
}
