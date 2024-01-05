///
/// @file       08-no-loops-condition-logic.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 4, 2024
/// @version    0.2
/// @brief      The use of function, enumeration and boolean algebra.
/// @note       The use of condition expressions, logic expressions, 
///             relation expressions and loops are not allowed in this file.
///

#include <iostream>

int myfun(int* arr) {
    // Step 1: use as many local variables as possible for easier calculation
    int result, sum = 0, product = 1;
    bool result_is_product = true;
    bool not_zero = true;
    // if current element is not zero
    not_zero = arr[0];
    // the result to return is flipped, else do not change the value
    result_is_product = (not_zero * (true - result_is_product)) +
                        ((true - not_zero) * (result_is_product));
    // add the element to the sum and multiply the product
    sum += arr[0];
    product *= ((int)not_zero * arr[0] + (int)(true - not_zero));
    // do the things above 7 times (7 is the size of input elements in function
    // "main") If the question does not imply the size, this function must
    // involve an infinite loop to finish calculation.
    not_zero = arr[1];
    result_is_product = (not_zero * (true - result_is_product)) +
                        ((true - not_zero) * (result_is_product));
    sum += arr[1];
    product *= ((int)not_zero * arr[1] + (int)(true - not_zero));
    // 2
    not_zero = arr[2];
    result_is_product = (not_zero * (true - result_is_product)) +
                        ((true - not_zero) * (result_is_product));
    sum += arr[2];
    product *= ((int)not_zero * arr[2] + (int)(true - not_zero));
    // 3
    not_zero = arr[3];
    result_is_product = (not_zero * (true - result_is_product)) +
                        ((true - not_zero) * (result_is_product));
    sum += arr[3];
    product *= ((int)not_zero * arr[3] + (int)(true - not_zero));
    // 4
    not_zero = arr[4];
    result_is_product = (not_zero * (true - result_is_product)) +
                        ((true - not_zero) * (result_is_product));
    sum += arr[4];
    product *= ((int)not_zero * arr[4] + (int)(true - not_zero));
    // 5
    not_zero = arr[5];
    result_is_product = (not_zero * (true - result_is_product)) +
                        ((true - not_zero) * (result_is_product));
    sum += arr[5];
    product *= ((int)not_zero * arr[5] + (int)(true - not_zero));
    // 6
    not_zero = arr[6];
    result_is_product = (not_zero * (true - result_is_product)) +
                        ((true - not_zero) * (result_is_product));
    sum += arr[6];
    product *= ((int)not_zero * arr[6] + (int)(true - not_zero));
    // What to return? Let's determine it.
    result = ((int)result_is_product * product +
              (int)(true - result_is_product) * sum);
    return result;
}

int main(int argc, const char* argv[]) {
    int arr[7];
    std::cout << "Input: " << std::flush;
    std::cin >> arr[0] >> arr[1] >> arr[2] >> arr[3] >> arr[4] >> arr[5] >>
        arr[6];
    std::cout << "Output: " << myfun(arr) << std::endl;
    return 0;
}
