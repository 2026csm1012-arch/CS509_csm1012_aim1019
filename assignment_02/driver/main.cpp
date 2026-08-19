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
        cout << "1. Triangle Counting\n";
        cout << "2. Betweenness Centrality\n";
        cout << "3. Connected Components\n";
        cout << "0. Exit\n";
        cout << "=========================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                runTriangleCounting();
                break;

            case 2:
                runBetweennessCentrality();
                break;

            case 3:
                runConnectedComponents();
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
