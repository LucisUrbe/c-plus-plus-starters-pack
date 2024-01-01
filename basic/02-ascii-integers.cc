///
/// @file       02-ascii-integers.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 1, 2024
/// @version    0.2
/// @brief      The use of integers, ASCII and standard I/O.
///

#include <iostream>

int main() {
    char c_1, c_2;

    // Step 1: input two English letters.
    std::cout << "Input: ";
    std::cin >> c_1;
    std::cout << "Input: ";
    std::cin >> c_2;

    // Step 2: reuse the local variables to store the offset
    if (c_1 >= 'a' && c_1 <= 'z')
        c_1 = c_1 - 'a' + 1;
    else if (c_1 >= 'A' && c_1 <= 'Z')
        c_1 = c_1 - 'A' + 1;

    if (c_2 >= 'a' && c_2 <= 'z')
        c_2 = c_2 - 'a' + 1;
    else if (c_2 >= 'A' && c_2 <= 'Z')
        c_2 = c_2 - 'A' + 1;

    // Step 3: output the offset
    if (c_1 < 10) {
        if (c_2 < 10)
            std::cout << "Output: 0" << (int)c_1 << '0' << (int)c_2 << std::endl;
        else
            std::cout << "Output: 0" << (int)c_1 << (int)c_2 << std::endl;
    }
    else if (c_2 < 10)
            std::cout << "Output: " << (int)c_1 << '0' << (int)c_2 << std::endl;
        else
            std::cout << "Output: " << (int)c_1 << (int)c_2 << std::endl;

    return 0;
}
