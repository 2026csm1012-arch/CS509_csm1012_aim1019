#include <cstdlib>
#include <iostream>
#include <string>

int main()
{
    std::cout << "\n";
    std::cout << "==========================================\n";
    std::cout << "       Graph Assignment Runner\n";
    std::cout << "==========================================\n";
    std::cout << "\n";

    std::cout << "Select an assignment:\n";
    std::cout << "  1. Assignment 01\n";
    std::cout << "  2. Assignment 02\n";
    std::cout << "  3. Assignment 03\n";
    std::cout << "\n";

    std::cout << "Enter your choice (1-3): ";

    int choice;

    if (!(std::cin >> choice))
    {
        std::cerr << "Invalid input.\n";
        return 1;
    }

    std::string command;

    switch (choice)
    {
        case 1:
            command = "cd assignment_01 && ./graph_runner";
            break;

        case 2:
            command = "cd assignment_02 && ./graph_runner";
            break;

        case 3:
            command = "cd assignment_03 && ./graph_runner";
            break;

        default:
            std::cerr << "Invalid choice. Please enter 1, 2, or 3.\n";
            return 1;
    }

    std::cout << "\nStarting Assignment " << choice << "...\n\n";

    int result = std::system(command.c_str());

    if (result != 0)
    {
        std::cerr << "\nAssignment " << choice
                  << " exited with an error.\n";
        return result;
    }

    return 0;
}
