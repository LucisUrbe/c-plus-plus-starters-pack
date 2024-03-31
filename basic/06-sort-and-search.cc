///
/// @file       06-sort-and-search.cc
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 3, 2024
/// @version    0.2
/// @brief      The use of bubble sort and binary search.
///

#include <iostream>

int main(int argc, const char* argv[]) {
    // Step 1: use a 1-d array to store a 4x4 matrix and input all the integers
    int a[16], low, high, mid, input;
    bool finished, right = true, down = true;
    std::cout << "Input: ";
    for (int i = 0; i < 16; i++)
        std::cin >> a[i];
    // Step 2: use bubble sort, time complexity: O(n*n)
    for (int i = 1; i < 16; i++) {
        // Here the boolean is for determining an ordered array
        finished = true;
        for (int j = 0; j < 16 - i; j++) {
            if (a[j] < a[j + 1]) {
                finished = false;
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
        if (finished)
            break;
    }
    // Step 3: use binary search to find the input integer
    std::cout << "Input: ";
    std::cin >> input;
    std::cout << "Output: ";
    low = 0;
    high = 15;
    while (low <= high) {
        mid = (low + high) / 2;
        if (input == a[mid])
            break;
        if (input < a[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (low > high)
        std::cout << "Not Found" << std::endl;
    else {
        // The question is deteministic so just enumerate!
        switch (mid) {
            case 0:
                std::cout << "0, 0" << std::endl;
                break;
            case 1:
                std::cout << "0, 1" << std::endl;
                break;
            case 2:
                std::cout << "0, 2" << std::endl;
                break;
            case 3:
                std::cout << "0, 3" << std::endl;
                break;
            case 4:
                std::cout << "1, 3" << std::endl;
                break;
            case 5:
                std::cout << "2, 3" << std::endl;
                break;
            case 6:
                std::cout << "3, 3" << std::endl;
                break;
            case 7:
                std::cout << "3, 2" << std::endl;
                break;
            case 8:
                std::cout << "3, 1" << std::endl;
                break;
            case 9:
                std::cout << "3, 0" << std::endl;
                break;
            case 10:
                std::cout << "2, 0" << std::endl;
                break;
            case 11:
                std::cout << "1, 0" << std::endl;
                break;
            case 12:
                std::cout << "1, 1" << std::endl;
                break;
            case 13:
                std::cout << "1, 2" << std::endl;
                break;
            case 14:
                std::cout << "2, 2" << std::endl;
                break;
            case 15:
                std::cout << "2, 1" << std::endl;
                break;
            default:
                std::cout << "Internal Method Error. Sorry about this!" << std::endl;
        }
    }
    return 0;
}
