///
/// @file       10-swap-two-strings.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 6, 2024
/// @version    0.2
/// @brief      The use of swap method, pointers and addresses.
/// @note       Do not include libraries other than "iostream".
///             ONLY ONE char, ONE char pointer, TWO char arrays are
///             allowed to be defined. The only char should ONLY be 
///             assigned. DO NOT use it for calculation.
///

#include <iostream>

int main(int argc, const char* argv[]) {
    // Step 1: define variables allowed with initialization (C++ 11 feature)
    char letter, *counter, a[20] = {0}, b[20] = {0};
    // Step 2: input the two stings
    std::cout << "Input: " << std::flush;
    std::cin.getline(a, 20);
    std::cout << "Input: " << std::flush;
    std::cin.getline(b, 20);
    // Step 3: swap the shorter one with the same partition of the longer one
    for (counter = &a[0]; a[counter - &a[0]] != '\0' && b[counter - &a[0]] != '\0'; counter++) {
        letter = a[counter - &a[0]];
        a[counter - &a[0]] = b[counter - &a[0]];
        b[counter - &a[0]] = letter;
    }
    // Step 4: output the result after swap
    std::cout << "Output: " << a << std::endl;
    std::cout << "Output: " << b << std::endl;
    return 0;
}
