///
/// @file       01-average-and-rounding.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       December 31, 2023
/// @version    0.2
/// @brief      The use of integers, math library and standard I/O.
///

#include <iostream>
#include <cmath>

int main() {
    unsigned int i_1, i_2, i_avg;
    double d_1, d_2, d_avg;

    // Step 1: input two unsigned integers and two doubles
    std::cout << "Input: ";
    std::cin >> i_1;
    std::cout << "Input: ";
    std::cin >> i_2;
    std::cout << "Input: ";
    std::cin >> d_1;
    std::cout << "Input: ";
    std::cin >> d_2;

    // Step 2: Calculate the average of the four numbers and output it
    d_avg = ((double)i_1 + (double)i_2 + d_1 + d_2) / 4;
    std::cout << "Output: " << d_avg << std::endl;

    // Step 3: Do rounding and output it
    i_avg = round(d_avg);
    std::cout << "Output: " << i_avg << std::endl;

    return 0;
}
