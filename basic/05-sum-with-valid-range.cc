///
/// @file       05-sum-with-valid-range.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 2, 2024
/// @version    0.2
/// @brief      The use of math theorem, permutation and logic.
///

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    int invalid = 233, valid = 233, counter, sum = 0;
    std::vector<int> result;
    while (invalid != 0) {
        std::cout << "Input: ";
        std::cin >> invalid;
    }
    // Possible improvement: reduce space complexity to O(1).
    for (counter = 0; valid != 0; counter++) {
        std::cout << "Input: ";
        std::cin >> valid;
        result.insert(result.begin() + counter, valid);
    }
    for (int i = 0; i < counter; i++) {
        sum += result[i];
    }
    std::cout << "Output: " << sum << std::endl;
    return 0;
}
