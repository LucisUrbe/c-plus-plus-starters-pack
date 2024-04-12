///
/// @file       measureLinkedBinaryTree.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       April 12, 2024
/// @version    0.2
/// @brief      Measure the size or height of a linked binary tree.
///

#include "linkedBinaryTree.hh"

namespace treeMeasurement {
    template <typename Type>
    int sizeOfTree(typename linkedBinaryTree<Type>::node* tree) {
        if (tree == nullptr)
            return 0;
        return 1 + sizeOfTree(tree -> leftNode) + sizeO(tree -> rightNode);
    }
    template <typename Type>
    int heightOfTree(typename linkedBinaryTree<Type>::node* tree) {
        if (tree == nullptr)
            return 0;
        else {
            int leftHeight = heightOfTree(tree -> leftNode), rightHeight = heightOfTree(tree -> rightNode);
            return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
        }
    }
}
