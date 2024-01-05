///
/// @file       09-function-fixed-return.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 4, 2024
/// @version    0.2
/// @brief      The use of static function variable.
/// @note       Do not overload functions. No global variables.
///             No more than three semicolons(;) and no commas(,) in function "SpaceCounter".
///             Do not include libraries other than "iostream".
///             The function "main" must completely executed without early exit.
///

#include <iostream>

int SpaceCounter(double) {
    static int called_times = 0;
    called_times++;
    return ((int)(called_times <= 3) * 4 * called_times) +
           ((int)(called_times > 3) * 8 * (called_times - 3));
}

int main(int argc, const char* argv[]) {
    int a[3];
    double b[3];

    std::cout << SpaceCounter(a[0]);
    std::cout << SpaceCounter(a[1]);
    std::cout << SpaceCounter(a[2]);
    std::cout << SpaceCounter(b[0]);
    std::cout << SpaceCounter(b[1]);
    std::cout << SpaceCounter(b[2]);

    return 0;
}
