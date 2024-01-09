///
/// @file       17-another-source-main.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 8, 2024
/// @version    0.2
/// @brief      The use of "extern" keyword.
///

#include <iostream>
using namespace std;

int myfun(int);
int yourfun(int);

int main() {
    int n;
    cout << "Input: ";
    cin >> n;
    cout << "Output: ";
    cout << myfun(n) << endl;
    return 0;
}

int myfun(int n) {
    extern int x; // Add "extern" to import global x = 10 from another cpp file. Only establish the aim in this way.
    return yourfun(n + x);
}
