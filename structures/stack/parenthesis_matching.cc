///
/// @file       parenthesis_matching.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       February 3, 2024
/// @version    0.2
/// @brief      The main process of parenthesis matching program.
///

#include <cstring>
#include "parenthesis_matching.hh"

int main(int argc, const char* argv[]) {
    try {
        if (argc == 1) {
            std::string input;
            std::cout << "Input the file name to check parenthesis matching: " << std::flush;
            std::cin >> input;
            char* fileName = new char[input.length()];
            strcpy(fileName, input.c_str());
            matching* m = new matching(fileName);
            int errors = m -> checkIfMatching();
            delete m;
            std::cout << "Total " << errors << " matching errors." << std::endl;
            return 0;
        }
        while (--argc) {
            std::cout << "Checking file: " << *++argv << std::endl;
            matching* m = new matching(*argv);
            int errors = m -> checkIfMatching();
            delete m;
            std::cout << "Total " << errors << " matching errors." << std::endl;
        }
    } catch (noFileException) {
        std::cout << "[ERROR] The file does not exist." << std::endl;
        return 404;
    }
    return 0;
}
