///
/// @file       07-rearrange-words.cc
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 3, 2024
/// @version    0.2
/// @brief      The use of math theorem, permutation and logic.
///

#include <iostream>

int main(int argc, const char* argv[]) {
    char words[10][11], sentence[110], key = ' ';
    int counter = 0, length[10] = {0}, total_length[10] = {0};
    // Step 1: input a sentence without a full stop(.)
    std::cout << "Input: ";
    std::cin.getline(sentence, 110);
    std::cout << "Output: ";
    // Step 2: count how many words the sentence has
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (key == ' ' && sentence[i] != ' ')
            counter++;
        key = sentence[i];
    }
    // Step 3: count how many characters each word has
    key = ' ';
    for (int i = -1, j = 0; i < counter && key != '\0'; j++) {
        if (key == ' ' && sentence[j] != ' ')
            i++;
        while (sentence[j] != '\0')
            if (sentence[j] != ' ') {
                length[i]++;
                j++;
            }
            else
                break;
        key = sentence[j];
    }
    // Step 4: split the words and store them into an array
    for (int i = 0, k = 0; i < counter; i++) {
        for (int j = 0; j < length[i]; j++, k++)
            words[i][j] = sentence[k];
        while (sentence[k] == ' ')
            k++;
    }
    // Step 5: calculate total lengths of the words with
    //          the same possible length (1~10)
    for (int i = 1; i <= 10; i++)
        for (int j = 0; j < counter; j++)
            if (length[j] == i)
                total_length[i - 1] += i;
    // Step 6: throughtout traverse, output the words with 
    //          the same length pieced-together with respect to
    //          the total length, from shorter to longer
    // The total lengths are small so just brute force
    for (int sum = 1; sum <= 100; sum++) 
        for (int i = 0; i < 10; i++) 
            if (total_length[i] == sum) {
                for (int j = 0; j < counter; j++)
                    if (length[j] == i + 1)
                        for (int k = 0; k < length[j]; k++)
                            std::cout << words[j][k];
                
                std::cout << ' ';
            }
    std::cout << std::flush;
    return 0;
}
