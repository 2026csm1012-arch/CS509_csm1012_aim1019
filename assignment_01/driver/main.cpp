#include <iostream>

#include "runner.h"

using namespace std;

int main()
{
    int choice;

    while (true)
    {
        cout << "\n";
        cout << "=========================================\n";
        cout << "      Graph Algorithms Test Runner\n";
        cout << "=========================================\n";
        cout << "1. Breadth First Search (BFS)\n";
        cout << "2. Depth First Search (DFS)\n";
        cout << "3. Single Source Shortest Path (SSSP)\n";
        cout << "0. Exit\n";
        cout << "=========================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                runBFS();
                break;

            case 2:
                runDFS();
                break;

            case 3:
                runSSSP();
                break;

            case 0:
                cout << "\nExiting...\n";
                return 0;

            default:
                cout << "\nInvalid choice.\n";
        }
    }

    return 0;
}