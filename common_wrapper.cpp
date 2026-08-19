#include <cstdlib>
#include <iostream>

using namespace std;

void run_assignment_01()
{
    if (system("make -C assignment_01") != 0)
    {
        cout << "Assignment 1 build failed.\n";
        return;
    }

    system("cd /d .\\assignment_01 && graph_runner.exe");
}
void run_assignment_02()
{
    if (system("make -C assignment_02") != 0)
    {
        cout << "Assignment 2 build failed.\n";
        return;
    }

    system("cd /d .\\assignment_02 && graph_runner.exe");
}
void run_assignment_03()
{
    if (system("make -C assignment_03") != 0)
    {
        cout << "Assignment 3 build failed.\n";
        return;
    }

    system("cd /d .\\assignment_03 && graph_runner.exe");
}

int main()
{
    int choice = 0;

    cout << "\n";
    cout << "====================================\n";
    cout << "        CS509 Assignment Wrapper\n";
    cout << "====================================\n\n";

    cout << "1. Assignment 1\n";
    cout << "2. Assignment 2\n";
    cout << "3. Assignment 3\n";
    cout << "0. Exit\n\n";

    cout << "Enter assignment number: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        run_assignment_01();
        break;

    case 2:
        run_assignment_02();
        break;

    case 3:
        run_assignment_03();
        break;

    case 0:
        cout << "\nExiting.\n";
        return 0;

    default:
        cout << "\nInvalid assignment number.\n";
        return 1;
    }
}