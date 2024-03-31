///
/// @file       03-four-cocyclic-points.cc
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 2, 2024
/// @version    0.2
/// @brief      The use of math theorem, permutation and logic.
///

#include <cmath>
#include <iostream>

int main() {
    int i_x1, i_y1;
    int i_x2, i_y2;
    int i_x3, i_y3;
    int i_x4, i_y4;
    double k[6];

    // Step 1: input four integer X-Y coordinates
    std::cout << "Input: ";
    std::cin >> i_x1 >> i_y1;
    std::cout << "Input: ";
    std::cin >> i_x2 >> i_y2;
    std::cout << "Input: ";
    std::cin >> i_x3 >> i_y3;
    std::cout << "Input: ";
    std::cin >> i_x4 >> i_y4;

    // Step 2: calculate each length of six possible sides
    k[0] = sqrt(double((i_x1 - i_x2) * (i_x1 - i_x2) + (i_y1 - i_y2) * (i_y1 - i_y2)));
    k[1] = sqrt(double((i_x1 - i_x3) * (i_x1 - i_x3) + (i_y1 - i_y3) * (i_y1 - i_y3)));
    k[2] = sqrt(double((i_x1 - i_x4) * (i_x1 - i_x4) + (i_y1 - i_y4) * (i_y1 - i_y4)));
    k[3] = sqrt(double((i_x2 - i_x3) * (i_x2 - i_x3) + (i_y2 - i_y3) * (i_y2 - i_y3)));
    k[4] = sqrt(double((i_x2 - i_x4) * (i_x2 - i_x4) + (i_y2 - i_y4) * (i_y2 - i_y4)));
    k[5] = sqrt(double((i_x3 - i_x4) * (i_x3 - i_x4) + (i_y3 - i_y4) * (i_y3 - i_y4)));

    // Step 3: using Ptolemy's theorem to determine if four coordinates are cocyclic
    bool success_flag = false;
    for (int a = 0; a < 6; a++) {
        for (int b = 0; b < 6; b++) {
            if (b != a)
            for (int c = 0; c < 6; c++) {
                if (c != b && c != a)
                for (int d = 0; d < 6; d++) {
                    if (d != c && d != b && d != a)
                    for (int e = 0; e < 6; e++) {
                        if (e != d && e != c && e != b && e != a)
                        for (int f = 0; f < 6; f++)
                            if (f != e && f != d && f != c && f != b && f != a)
                                if (fabs(k[a] * k[b] - k[c] * k[d] - k[e] * k[f]) <= 1.0E-10) {
                                    std::cout << "Output: Yes" << std::endl;
                                    success_flag = true;
                                    break;
                                }
                        if (success_flag)
                            break;
                    }
                    if (success_flag)
                        break;
                }
                if (success_flag)
                    break;
            }
            if (success_flag)
                break;
        }
        if (success_flag)
            break;
    }

    if (!success_flag)
        std::cout << "Output: No" << std::endl;
    return 0;
}
