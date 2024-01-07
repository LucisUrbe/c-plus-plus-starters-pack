///
/// @file       12-new-rearrange-words.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 6, 2024
/// @version    0.2
/// @brief      The use of standard library and ADT strings.
/// @note       The user just input no more than 100 characters
///             and each word has no more than 10 characters.
///

#include <iostream>

int main(int argc, const char* argv[]) {
    // Step 1: input a sentence without a full stop(.)
    std::string input;
    std::cout << "Input: ";
    std::getline(std::cin, input);
    // The last element of a char string is nullptr.
    char* sentence = new char[input.length() + 1];
    // Copy string to the char array "sentence".
    input.copy(sentence, input.length() + 1, 0);
    // Step 2: count the words input and output
    char key = ' ';
    int counter = 0;
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (key == ' ' && sentence[i] != ' ')
            counter++;
        key = sentence[i];
    }
    std::cout << "Output: " << counter << std::endl;
    // Step 3: calculate the length of each word and store in the array
    int* length = new int[counter];
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
    // Step 4: split each word and store in the 2-d array
    char** words = new char* [counter];
    for (int i = 0; i < counter; i++)
        words[i] = new char[length[i]];
    for (int i = 0, k = 0; i < counter; i++) {
        for (int j = 0; j < length[i]; j++, k++)
            words[i][j] = sentence[k];
        while (sentence[k] == ' ')
            k++;
    }
    // Release the heap memory of "sentence".
    delete [] sentence;
    // Step 5: input the new order of the words
    char* order = new char[counter];
    std::cout << "Input: ";
    for (int i = 0; i < counter; i++)
        std::cin >> order[i];
    // Convert char array to int array.
    int* result = new int[counter];
    for (int i = 0; i < counter; i++)
        result[i] = order[i] - '0';
    std::cout << "Output: ";
    for (int i = 0; i < counter; i++) {
        for (int j = 0; j < length[result[i]]; j++)
            std::cout << words[result[i]][j];
        std::cout << ' ';
    }
    // Release the heap memory of "length", "words", "order", "result".
    for (int i = 0; i < counter; i++)
        delete [] words[i];
    delete [] length, words, order, result;
    return 0;
}
