///
/// @file       13-pointers-and-overload.cc
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 6, 2024
/// @version    0.2
/// @brief      The use of standard library and reference.
/// @note       The user just input no more than 100 characters
///             and each word has no more than 10 characters.
///

#include <iostream>
using namespace std;

// Fill two lines of code below.
#define ABS_INT(integer) ((integer >= 0)? integer : -integer)
string myfun(int &a, int &b);
// Fill two lines of code above.
int myfun(int *a, int *b);

int main(int argc, char* argv[]) {
    int x, y;
    cout << "Input: ";
    cin >> x >> y;
    cout << "Output: ";
    cout << myfun(x, y);
    cout << x << ' ' << y;
    return 0;
}

int myfun(int *a, int *b) {
    int c = *a - *b;
    *a *= 2;
    *b *= 3;
    return c;
}

// Define a function below.
/// @note   This function must contain NO MORE THAN 2 semicolons(;)
///         and NO commas(,) unless it is for function parameters.
string myfun(int &a, int &b) {
    int first = myfun(&b, &a);
    return to_string(ABS_INT(first) % 10) + string(" ");
}
