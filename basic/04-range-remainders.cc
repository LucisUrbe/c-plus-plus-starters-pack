///
/// @file       04-range-remainders.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 2, 2024
/// @version    0.2
/// @brief      The use of math theorem, permutation and logic.
///

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    int m, n, x, counter = 0;
    std::vector<int> result;
    // Step 1: input the value of m, n, x
    std::cout << "Input: m=";
    std::cin >> m;
    std::cout << "Input: n=";
    std::cin >> n;
    std::cout << "Input: x=";
    std::cin >> x;
    std::cout << "Outputs:" << std::endl;
    // Step 2: when all inputs valid, 
    //          traverse the range and output remainders less than 5
    if (x > 0 && m > x && n > m) {
        for (int output = m; output <= n; output++) {
            int remainder = output % x;
            if (remainder < 5) {
                std::cout << output << std::endl;
                result.insert(result.begin() + counter, output);
                counter++;
            }
        }
        if (counter == 0) {
            std::cout << "NONE" << std::endl;
        }
        int sum = 0;
        for (int i = 0; i < counter; i++) {
            sum += result[i] * result[i];
        }
        std::cout << "Sum of Squares: " << sum << std::endl;
    }
    else {
        std::cout << "Input(s) invalid. Inputs must satisfy 0<x<m<n!" << std::endl;
    }
    return 0;
}
