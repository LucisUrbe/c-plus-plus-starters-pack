///
/// @file       13-pointers-and-overload
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 8, 2024
/// @version    0.2
/// @brief      The use of function, reference and pointers.
/// @note       Please ensure no memory leaks during runtime.
///

#include <iostream>
#include <cstring>
using namespace std;

// Declare two functions below.

char* &funA(char** &);
char* funB(char*, char* &);

int main() {
    char a[10], b[10];
    for (int i=0; i<2; ++i) {
        char **p;
        cout << "Input: ";
        cin >> a;
        funA(p) = a;
        cout << "Output: ";
        cout << funB(b, *p);
    }
    return 0;
}

// Define two functions below.

/// @brief  This function is to create a char pointer so
///         that the reference type matches the RHS.
/// @note   This function is used as left value,
///         so the return type must be reference.
char* &funA(char** &p) {
    p = new char*;
    return *p;
}

/// @note   The string must have no more than 8 chars.
char* funB(char* invalid, char* &p) {
    short length = strlen(p);
    if (length > 8) {
        cout << "PANIC: illegal input" << endl;
        exit(-1);
    }
    for (short i = 0; i < length; i++)
        if (p[i] - '0' > 0 && p[i] - '0' <= 9)
            p[i] = '0';
    p[length] = '\n';
    p[length + 1]= '\0';
    return p;
}
