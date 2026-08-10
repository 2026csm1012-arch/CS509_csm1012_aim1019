#include "compare.h"

#include <fstream>
#include <iostream>
#include <string>

//------------------------------------------------------
// Compare Two Output Files
//------------------------------------------------------
bool compareFiles(const std::string &expectedFile,
                  const std::string &generatedFile)
{
    std::ifstream expected(expectedFile);
    std::ifstream generated(generatedFile);

    if (!expected.is_open())
    {
        std::cout << "Cannot open: "
                  << expectedFile
                  << std::endl;

        return false;
    }

    if (!generated.is_open())
    {
        std::cout << "Cannot open: "
                  << generatedFile
                  << std::endl;

        return false;
    }

    std::string line1;
    std::string line2;

    int lineNo = 1;

    while (true)
    {
        bool ok1 = static_cast<bool>(std::getline(expected, line1));
        bool ok2 = static_cast<bool>(std::getline(generated, line2));

        if (!ok1 && !ok2)
            return true;

        if (ok1 != ok2)
        {
            std::cout << "\nDifferent number of lines.\n";
            return false;
        }

        if (line1 != line2)
        {
            std::cout << "\nDifference at line "
                      << lineNo
                      << std::endl;

            std::cout << "Expected : "
                      << line1
                      << std::endl;

            std::cout << "Generated: "
                      << line2
                      << std::endl;

            return false;
        }

        lineNo++;
    }
}