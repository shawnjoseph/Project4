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
        command_state = DGraph;
    } else if (cmd == "UndirectedGraph") {
        command_state = UGraph;
    } else {
        cout << "Quit command\n";
        command_state = Done;
    }
}


void CommandProcessor::ProcessDirectedGraph(const string &cmd) {
    if (cmd == "Insert") {
        // Fill part in with getting info
        diGraph->insert(node, parentKey);
    } else if (cmd == "Build Graph") {
        diGraph->buildTree();
    } else if (cmd == "Clear") {
        diGraph->clear();
    } else if (cmd == "Reset") {
        diGraph->buildTree();
    } else if (cmd == "Delete") {
        string data;
        cout << "What data does the TreeNode you want to delete have?" << endl;
        getline(cin, data);
        TreeNode <string> *node = new TreeNode<string>("General", data);
        diGraph->del(node);
    } else if (cmd == "Indegree") {
        diGraph->indegree();
    } else if (cmd == "Outdegree") {

    } else if (cmd == "Edgecount") {

    } else if (cmd == "Adjacent") {

    } else if (cmd == "Depth First Search") {

    } else if (cmd == "Breadth First Search") {

    } else if (cmd == "Distance") {

    } else if (cmd == "Short Path") {

    } else if (cmd == "Is Empty") {
        diGraph->empty();
    } else if (cmd == "Exit") {
        exit(0);
    } else {
        cout << "Error" << endl;
    }
}

void CommandProcessor::ProcessUndirectedGraph(const string &cmd) {
    if (cmd == "Max") {
        cout << "Max: " << "Key[" << graph->getMax()->getKey() << "]"
        << " Value[" << graph->getMax()->getValue() << "]" << endl;
    } else if (cmd == "Size") {
        cout << "Size: " << graph->getSize() << endl;
    } else if (cmd == "Height") {
        cout << "Height: " << graph->getHeight() << endl;
    } else if (cmd == "Empty") {
        if (graph->empty()) {
            cout << "Heap is empty." << endl;
        }
        else {
            cout << "Heap is Not Empty." << endl;
        }
    } else if (cmd == "Leaves") {
        cout << "Number of Leaves: " << graph->leaves() << endl;
    } else if (cmd == "Build Tree") {
        graph->buildTree();
    } else if (cmd == "Clear") {
        graph->clear();
    } else if (cmd == "Insert") {
        int key;
        string value;
        cout << "Enter key: ";
        cin >> key;
        while (cin.fail()) {
            cout << "Error" << std::endl;
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Enter key: ";
            cin >> key;
        }
        getchar();
        cout << "Enter value: ";
        getline(cin, value);
        graph->insert(key, value);
    } else if (cmd == "Delete Max") {
        int max = graph->getMax()->getKey();
        graph->delMax();
        cout << "Max " << max << " deleted." << endl;
    } else if (cmd == "Display") {
        graph->Display();
    } else if (cmd == "Exit") {
        exit(0);
    } else {
        cout << "Error" << endl;
    }
}

void CommandProcessor::Create_Menus() {
    // Menu for Initial command state
    Menu *menu = new Menu("Which Tree do you want to create?");
    menu->Add_Command("Tree");
    menu->Add_Command("Heap");
    menu->Add_Command("AVLTree");

    menus[Initial] = menu;

    //Menu for Tree
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
    menus[_Tree] = menu;

    //Menu for Heap
    menu = new Menu("Enter command number:\n");
    menu->Add_Command("Max");
    menu->Add_Command("Size");
    menu->Add_Command("Height");
    menu->Add_Command("Empty");
    menu->Add_Command("Leaves");
    menu->Add_Command("Build Tree");
    menu->Add_Command("Clear");
    menu->Add_Command("Insert");
    menu->Add_Command("Delete Max");
    menu->Add_Command("Display");
    menu->Add_Command("Exit");
    menus[_Heap] = menu;

    //Menu for AVLTree
    menu = new Menu("Enter command number:\n");
    menu->Add_Command("Get Root");
    menu->Add_Command("Get Size");
    menu->Add_Command("Get Height");
    menu->Add_Command("Get Depth");
    menu->Add_Command("Is Empty");
    menu->Add_Command("Get Leaves");
    menu->Add_Command("Get Siblings");
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
    menus[_AVLTree] = menu;
}
