///
/// @file       HuffmanTree.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       April 20, 2024
/// @version    0.2
/// @brief      The Huffman Tree program, creating a Huffman Tree from given characters and their corresponding weights.
///

#include <string>

template<typename Type>
class HuffmanTree {
private:
    struct node {
        Type data;
        int weight;
        int parent_P, left_P, right_P;
    };
    node *element;
    int length;
public:
    struct HuffmanCode {
        Type data;
        std::string code;
    };

    HuffmanTree(const Type *toEncode, const int *codeWeight, int size) {
        //const int INT16_MAX = 32767;
        int minWeight_1, minWeight_2, min_1_P, min_2_P;
        length = 2 * size;
        element = new node[length];
        for (int i = size; i < length; i++) {
            element[i].data = toEncode[i - size];
            element[i].weight = codeWeight[i - size];
            element[i].parent_P = element[i].left_P = element[i].right_P = 0;
        }
        for (int i = size - 1; i > 0; i--) {
            minWeight_1 = minWeight_2 = INT16_MAX;
            min_1_P = min_2_P = 0;
            for (int j = i + 1; j < length; j++)
                if (element[j].parent_P == 0) {
                    if (element[j].weight < minWeight_1) {
                        minWeight_2 = minWeight_1;
                        minWeight_1 = element[j].weight;
                        min_2_P = min_1_P;
                        min_1_P = j;
                    } else if (element[j].weight < minWeight_2) {
                        minWeight_2 = element[j].weight;
                        min_2_P = j;
                    }
                }
            element[i].weight = minWeight_1 + minWeight_2;
            element[i].left_P = min_2_P;
            element[i].right_P = min_1_P;
            element[i].parent_P = 0;
            element[min_1_P].parent_P = i;
            element[min_2_P].parent_P = i;
        }
    }

    ~HuffmanTree() {
        delete[] element;
    }

    void getCode(HuffmanCode result[]) {
        int size = length / 2;
        int current_P, current_parent_P;
        for (int i = size; i < length; i++) {
            result[i - size].data = element[i].data;
            result[i - size].code = "";
            current_P = i;
            current_parent_P = element[i].parent_P;
            while (current_parent_P) {
                if (element[current_parent_P].left_P == current_P)
                    result[i - size].code = '0' + result[i - size].code;
                else
                    result[i - size].code = '1' + result[i - size].code;
                current_P = current_parent_P;
                current_parent_P = element[current_parent_P].parent_P;
            }

        }
    }
};

#include <iostream>

int main(int argc, const char *argv[]) {
    char code_O[] = {"aeistdn"};
    int weight_O[] = {10, 15, 12, 3, 4, 13, 1};
    HuffmanTree<char> ht(code_O, weight_O, 7);
    HuffmanTree<char>::HuffmanCode result[7];
    ht.getCode(result);
    for (int i = 0; i < 7; i++)
        std::cout << result[i].data << ' ' << result[i].code << std::endl;
    return 0;
}
