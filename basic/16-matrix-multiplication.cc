///
/// @file       16-matrix-multiplication.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 8, 2024
/// @version    0.2
/// @brief      The use of pointers and matrix multiplication.
///

#include <iostream>
using namespace std;

// Declare function "myfun" below.
void myfun(int*, int*, int);

int main() {
    int n;
    cout << "Input n: ";
    cin >> n;
    cout << "Input A: ";
    // Write some code below.
    // A is an array of (int) pointers.
    int* A[3];
    for (int i = 0; i < 3; i++)
        A[i] = new int[n];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];
    cout << "Input B: ";
    // Write some code below.
    // B is a pointer to a dynamic 1-d array.
    int* B = new int[n * 3];
    for (int i = 0; i < n * 3; i++)
        cin >> B[i];
    cout << "Output:\n";
    for(int i = 0; i < 3; ++i)
        myfun(A[i], B, n);
    delete [] B;
    return 0;
}
// Define function "myfun" below.
void myfun(int* a, int* b, int n) {
    for (int i = 0; i < 3; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++)
            sum += a[j] * b[i + j * 3];
        cout << sum << ' ';
    }
    cout << endl;
}
