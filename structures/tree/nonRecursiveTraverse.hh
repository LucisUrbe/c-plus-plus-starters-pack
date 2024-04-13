///
/// @file       nonRecursiveTraverse.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       April 13, 2024
/// @version    0.2
/// @brief      Traverse a linked binary tree without recursive function calls.
///

#if !defined(_LIBCPP_IOSTREAM) || !defined(_GLIBCXX_IOSTREAM) || !defined(_IOSTREAM_)
    #include <iostream>
#endif
#include "../stack/linkedStack.hh"
#include "../queue/sequenceQueue.hh"
#include "linkedBinaryTree.hh"

namespace nonRecursiveTraverse {
    template <typename Type>
    void traversePreorder(typename linkedBinaryTree<Type>::node* rootNode) {
        if (!rootNode)
            return;
        linkedStack<typename linkedBinaryTree<Type>::node*> ls;
        typename linkedBinaryTree<Type>::node* current;
        std::cout << "Non-recursive preorder traverse: " << std::flush;
        ls.push(rootNode);
        while (!ls.isEmpty()) {
            current = ls.pop();
            std::cout << current -> data << std::flush;
            if (current -> rightNode != nullptr)
                ls.push(current -> rightNode);
            if (current -> leftNode != nullptr) // !!! !!! !!!
                ls.push(current -> leftNode);
        }
    }
    template <typename Type>
    void traverseInorder(typename linkedBinaryTree<Type>::node* rootNode) {
        if (!rootNode)
            return;
        linkedStack<typename linkedBinaryTree<Type>::node*> ls;
        linkedStack<short> ls_flag;
        typename linkedBinaryTree<Type>::node* current = rootNode;
        short flag;
        const short zero = 0, one = 1;
        ls.push(current);
        ls_flag.push(zero);
        while (!ls.isEmpty()) {
            flag = ls_flag.pop();
            current = ls.top();
            if (flag == 1) {
                ls.pop();
                std::cout << current -> data;
                if (!current -> rightNode)
                    continue;
                ls.push(current -> rightNode);
                ls_flag.push(zero);
            }
            else {
                ls_flag.push(one);
                if (current -> leftNode) {
                    ls.push(current -> leftNode);
                    ls_flag.push(zero);
                }
            }
        }
        std::cout << std::endl;
    }
    template <class Type>
    void traversePostorder(typename linkedBinaryTree<Type>::node* rootNode) {
        if (!rootNode)
            return;
        typename linkedBinaryTree<Type>::node* current;
        linkedStack<typename linkedBinaryTree<Type>::node*> ls;
        linkedStack<int> ls_flag;
        const int zero = 0, one = 1, two = 2;
        int flag;
        ls.push(rootNode);
        ls_flag.push(zero);
        while (!ls.isEmpty()) {
            flag = ls_flag.pop();
            current = ls.top();
            switch (flag) {
                case 2:
                    ls.pop();
                    std::cout << current -> data;
                    break;
                case 1:
                    ls_flag.push(two);
                    if (current -> rightNode) {
                        ls.push(current -> rightNode);
                        ls_flag.push(zero);
                    }
                    break;
                case 0:
                    ls_flag.push(one);
                    if (current -> left) {
                        ls.push(current -> leftNode);
                        ls_flag.push(zero);
                    }
                    break;
            } // switch
        } // while
    }
    template <typename Type>
    void traverseLevelOrder(typename linkedBinaryTree<Type>::node* rootNode) {
        if (!rootNode)
            return;
        sequenceQueue<typename linkedBinaryTree<Type>::node*> sq;
        typename linkedBinaryTree<Type>::node* current;
        sq.push(rootNode);
        while (!sq.empty()) {
            current = sq.pop();
            std::cout << current -> data;
            if (current -> leftNode)
                sq.push(current -> leftNode);
            if (current -> rightNode)
                sq.push(current -> rightNode);
        }
        std::cout << std::endl;
    }
}
