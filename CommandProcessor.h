#pragma once

#include <string>
#include <sstream>
#include "Menu.h"
#include "Digraph.h"
#include "Graph.h"

enum Command_States {
    Initial, DirectedGraph, UndirectedGraph, Done
};
using namespace std;

class CommandProcessor {
public:
    static void Process_Commands();

private:
    static const int NR_CMD_STATES = (int) Done + 1;
    static Command_States command_state;
    static Menu *menus[NR_CMD_STATES];

    static void Create_Menus();

    static void Process_Initial_Cmd(const string &cmd);

    static void ProcessDirectedGraph(const string &cmd);

    static void ProcessUndirectedGraph(const string &cmd);

    CommandProcessor(void) { };
};
