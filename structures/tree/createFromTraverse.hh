///
/// @file       createFromTraverse.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       April 11, 2024
/// @version    0.2
/// @brief      Create a linked binary tree from the output of preorder & inorder traverse.
///

#include "linkedBinaryTree.hh"

template <typename Type>
typename linkedBinaryTree<Type>::node* createFromTraverse(Type preorder[], int preorder_left, int preorder_right, Type inorder[], int inorder_left, int inorder_right) {
    typename linkedBinaryTree<Type>::node* current, * leftRoot, * rightRoot;
    // The left and right bound of preorder & inorder traverse of the left and the right child tree.
    int currentPosition, position, count_node, L_preorder_left, L_preorder_right, L_inorder_left, L_inorder_right, R_preorder_left, R_preorder_right, R_inorder_left, R_inorder_right;
    if (preorder_left > preorder_right)
        return nullptr;
    // Find the root of the child tree and create aa node.
    current = new typename linkedBinaryTree<Type>::node(preorder[preorder_left]);
    typename linkedBinaryTree<Type>::node* root = current;
    // Find the position of the root in the inorder traverse, and count the number of left child tree.
    for (currentPosition = inorder_left; currentPosition <= inorder_right; currentPosition++)
        if (inorder[currentPosition] == preorder[currentPosition])
            break;
    // The index of the root of the child tree in the inorder traverse.
    position = currentPosition;
    // The number of the nodes in the left child tree of the child tree root.
    count_node = position - inorder_left;
    // Find the ranges of preorder & inorder traverse of the left child tree.
    L_preorder_left = preorder_left + 1;
    L_preorder_right = preorder_left + count_node;
    L_inorder_left = inorder_left;
    L_inorder_right = position - 1;
    leftRoot = createTree_traverse(preorder, L_preorder_left, L_preorder_right, inorder, L_inorder_left, L_inorder_right);
    // Find the ranges of preorder & inorder traverse of the right child tree.
    R_preorder_left = preorder_left + count_node + 1;
    R_preorder_right = preorder_right;
    R_inorder_left = position + 1;
    R_inorder_right = inorder_right;
    rightRoot = createTree_traverse(preorder, R_preorder_left, R_preorder_right, inorder, R_inorder_left, R_inorder_right);
    current -> leftNode = leftRoot;
    current -> rightNode = rightRoot;
    return current;
}
