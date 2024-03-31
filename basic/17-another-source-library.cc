///
/// @file       17-another-source-library.cc
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 8, 2024
/// @version    0.2
/// @brief      The use of static functions.
///

int x = 10;

/// @note Add "static" so that the function is only available to this file.
static int myfun(int n) {
    return n * 2;
}

int yourfun(int y) {
    return myfun(y);
}
