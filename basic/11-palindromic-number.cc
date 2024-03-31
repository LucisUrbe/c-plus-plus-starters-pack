///
/// @file       11-palindromic-number.cc
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 6, 2024
/// @version    0.2
/// @brief      The use of recursive function calls.
/// @note       No more than 10 semicolons(;) and commas(,) total
///             in your self-written code.
///             You can ONLY write your own code in the areas given
///             (See comments in the functions). 
///             DO NOT call library functions in function "func".
///             DO NOT use loops. NO MORE self-defined objects.
///

#include <iostream>
#include <cstring>

using namespace std;

bool func(char array[], int len);

int main() {
    char ch[20];
    bool result;

    cout<< "Input: ";
    cin >> ch;

    // Write your own code below.
    // Note: boolean "result" is useless.
    if (func(ch, strlen(ch)))
        cout << "Output: Yes" << endl;
    else 
        cout << "Output: No" << endl;
    // 2 semicolons(;) & 1 comma(,)
    return 0;
}

bool func(char array[], int len) {
    // Write your own code below.
    if (len == 1 || len == 0)
        return true;
    if (array[0] == array[len - 1])
        if (func(array + 1, len - 2))
            return true;
    return false;
    // 3 semicolons(;) & 1 comma(,)
}
