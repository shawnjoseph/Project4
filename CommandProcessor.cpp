#include <iostream>
#include "CommandProcessor.h"

using namespace std;

Command_States CommandProcessor::command_state = Initial;
Menu *CommandProcessor::menus[NR_CMD_STATES];

Digraph<string> *diGraph = new Digraph<string>();
Graph<string> *graph = new Graph<string>();

void CommandProcessor::Process_Commands() {
    cout << "Process commands starting\n";


    Create_Menus();

    while (command_state != Done) {
        const string *cmd = menus[command_state]->Get_Command();

        switch (command_state) {
            case Initial:
                Process_Initial_Cmd(*cmd);
                break;

            case DirectedGraph:
                ProcessDirectedGraph(*cmd);
                break;

            case UndirectedGraph:
                ProcessUndirectedGraph(*cmd);
                break;

            case Done:
                break;      // Can't happen
        }
    }

    cout << "Command_Processor exiting\n";
    // Process command in Initial command state

}

void CommandProcessor::Process_Initial_Cmd(const string &cmd) {
    if (cmd == "DirectedGraph") {
        command_state = DirectedGraph;
    } else if (cmd == "UndirectedGraph") {
        command_state = UndirectedGraph;
    } else {
        cout << "Quit command\n";
        command_state = Done;
    }
}


void CommandProcessor::ProcessDirectedGraph(const string &cmd) {
    if (cmd == "Insert") {
        string u, v;
        double weight;
        cout << "Enter name of start vertex: ";
        getline(cin, u);
        cout << "Enter name of end vertex: ";
        getline(cin, v);
        cout << "Enter weight of edge between vertices: ";
        cin >> weight;
        getchar();
        diGraph->insert(u, v, weight);
        cout << "Edge added" << endl;
    } else if (cmd == "Build Graph") {
        diGraph->buildGraph();
        cout << "The graph has been built." << endl;
    } else if (cmd == "Clear") {
        diGraph->clear();
    } else if (cmd == "Reset") {
        diGraph->reset();
        cout << "Vertices have been reset." << endl;
    } else if (cmd == "Delete") {
        string v;
        cout << "Enter vertex to be deleted." << endl;
        getline(cin, v);
        diGraph->del(v);
    } else if (cmd == "Indegree") {
        string v;
        cout << "Enter vertex name: ";
        getline(cin, v);
        cout << "Indegree of " << v << " is: " << diGraph->indegree(v) << endl;
    } else if (cmd == "Outdegree") {
        string v;
        cout << "Enter vertex name: ";
        getline(cin, v);
        cout << "Outdegree of " << v << " is: " << diGraph->outdegree(v) << endl;
    } else if (cmd == "Edgecount") {
        cout << "There are " << diGraph->edgeCount() << " edges in the graph." << endl;
    } else if (cmd == "Adjacent") {
        string u, v;
        cout << "Enter name of start vertex: ";
        getline(cin, u);
        cout << "Enter name of end vertex: ";
        getline(cin, v);
        diGraph->adjacent(u, v);
    } else if (cmd == "Depth First Search") {
        string v;
        cout << "Enter name of start vertex: ";
        getline(cin, v);
        diGraph->DFS(v);
    } else if (cmd == "Breadth First Search") {
//        diGraph->BFS();
    } else if (cmd == "Distance") {
        string u, v;
        cout << "Enter name of start vertex: ";
        getline(cin, u);
        cout << "Enter name of end vertex: ";
        getline(cin, v);
        diGraph->distance(u, v);
    } else if (cmd == "Short Path") {
        string u, v;
        cout << "Enter name of start vertex: ";
        getline(cin, u);
        cout << "Enter name of end vertex: ";
        getline(cin, v);
        diGraph->shortPath(u, v);
    } else if (cmd == "Is Empty") {
        diGraph->empty();
    } else if (cmd == "Exit") {
        exit(0);
    } else {
        cout << "Error" << endl;
    }
}

void CommandProcessor::ProcessUndirectedGraph(const string &cmd) {
    if (cmd == "Build Graph") {
        graph->buildGraph();
        cout << "The graph has been built." << endl;
    } else if (cmd == "Empty") {
        graph->empty();
    } else if (cmd == "Insert") {
        string u, v;
        double weight;
        cout << "Enter name of start vertex: ";
        getline(cin, u);
        cout << "Enter name of end vertex: ";
        getline(cin, v);
        cout << "Enter weight of edge between vertices: ";
        cin >> weight;
        getchar();
        graph->insert(u, v, weight);
        cout << "Edge added" << endl;
    } else if (cmd == "Check Adjacency") {
        string u, v;
        cout << "Enter name of start vertex: ";
        getline(cin, u);
        cout << "Enter name of end vertex: ";
        getline(cin, v);
        graph->adjacent(u, v);
    } else if (cmd == "Find Degree") {
        string v;
        cout << "Enter name of vertex: " << endl;
        getline(cin, v);
        cout << "Degree of " << v << " is " << graph->degree(v) << endl;
    } else if (cmd == "Edge Count") {
        cout << "There are " << graph->edgeCount() << " edges in the graph." << endl;
    } else if (cmd == "Check Connection") {
        if (graph->isConnected()) {
            cout << "The graph is connected." << endl;
        } else {
            cout << "The graph is not connected." << endl;
        }
    } else if (cmd == "Clear") {
        graph->clear();
    } else if (cmd == "Reset Vertices") {
        graph->reset();
        cout << "Vertices have been reset." << endl;
    } else if (cmd == "Delete Vertex") {
        string v;
        cout << "Enter vertex to be deleted." << endl;
        getline(cin, v);
        graph->del(v);
    } else if (cmd == "Display") {
        graph->display();
    } else if (cmd == "Breadth-First Search") {
        string v;
        cout << "Enter name of start vertex: ";
        getline(cin, v);
        graph->BFS(v);
    } else if (cmd == "Depth-First Search") {
        string v;
        cout << "Enter name of start vertex: ";
        getline(cin, v);
        graph->DFS(v);
    } else if (cmd == "Find Minimum-Spanning Tree") {
        string v;
        cout << "Enter name of start vertex: ";
        getline(cin, v);
        graph->MST(v);
    } else if (cmd == "Exit") {
        exit(0);
    } else {
        cerr << "Error" << endl;
    }
}

void CommandProcessor::Create_Menus() {
    // Menu for Initial command state
    Menu *menu = new Menu("Which Graph would you like to create?");
    menu->Add_Command("DirectedGraph");
    menu->Add_Command("UndirectedGraph");

    menus[Initial] = menu;

    //Menu for DirectedGraph
    menu = new Menu("Enter command number:\n");
    menu->Add_Command("Get Root");
    menu->Add_Command("Get Size");
    menu->Add_Command("Get Height");
    menu->Add_Command("Get Depth");
    menu->Add_Command("Is Empty");
    menu->Add_Command("Get Leaves");
    menu->Add_Command("Get Siblings");
    menu->Add_Command("Find Common Ancestor");
    menu->Add_Command("Find Tree Node");
    menu->Add_Command("Preorder");
    menu->Add_Command("Postorder");
    menu->Add_Command("Levelorder");
    menu->Add_Command("Inorder");
    menu->Add_Command("Build Tree");
    menu->Add_Command("Clear");
    menu->Add_Command("Insert");
    menu->Add_Command("Delete");
    menu->Add_Command("Exit");
    menus[DirectedGraph] = menu;

    //Menu for UndirectedGraph
    menu = new Menu("Enter command number:\n");
    menu->Add_Command("Build Graph");
    menu->Add_Command("Empty");
    menu->Add_Command("Insert");
    menu->Add_Command("Check Adjacency");
    menu->Add_Command("Find Degree");
    menu->Add_Command("Edge Count");
    menu->Add_Command("Check Connection");
    menu->Add_Command("Clear");
    menu->Add_Command("Reset Vertices");
    menu->Add_Command("Delete Vertex");
    menu->Add_Command("Display");
    menu->Add_Command("Breadth-First Search");
    menu->Add_Command("Depth-First Search");
    menu->Add_Command("Find Minimum-Spanning Tree");
    menu->Add_Command("Exit");
    menus[UndirectedGraph] = menu;

}
