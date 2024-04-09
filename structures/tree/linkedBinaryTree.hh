///
/// @file       linkedBinaryTree.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       April 9, 2024
/// @version    0.2
/// @brief      The linked binary tree, storing elements in linked memory chains with maximum 3 degrees.
///

#if !defined(_LIBCPP_IOSTREAM) || !defined(_GLIBCXX_IOSTREAM) || !defined(_IOSTREAM_)
    #include <iostream>
#endif
#include "../queue/linkedQueue.hh"
#include "binaryTree.hh"

template <typename Type>
class linkedBinaryTree: public binaryTree<Type> {
    friend void printTree(const linkedBinaryTree<Type>& toPrint, Type flag);
private:
    struct node {
        node* leftNode, * rightNode;
        Type data;
        node(): leftNode(nullptr), rightNode(nullptr) {}
        node(Type rawData, node* leftSource = nullptr, node* rightSource = nullptr): data(rawData), leftNode(leftSource), rightNode(rightSource) {}
        ~node() {}
    };
    node* rootNode;
    node* find(Type toFind, node* toSearch) const;
    void preorderTraverse(node* toTraverse) const;
    void inorderTraverse(node* toTraverse) const;
    void postorderTraverse(node* toTraverse) const;
    void clear(node*& toClear);
public:
    linkedBinaryTree(): rootNode(nullptr) {}
    linkedBinaryTree(Type rawNode) {
        rootNode = new node(rawNode);
    }
    ~linkedBinaryTree();
    void clear();
    void create(Type flag);
    void deleteLeft(Type target);
    void deleteRight(Type target);
    void preorderTraverse() const;
    void inorderTraverse() const;
    void postorderTraverse() const;
    void levelOrderTraverse() const;
    bool empty() const;
    Type root(Type flag) const;
    Type parent(Type toFind, Type flag) const {
        return flag;
    }
    Type leftChild(Type toFind, Type flag) const;
    Type rightChild(Type toFind, Type flag) const;
};

template <typename Type>
void printTree(const linkedBinaryTree<Type>& toPrint, Type flag) {
    linkedQueue<Type> lq;
    lq.push(toPrint.rootNode -> data);
    std::cout << std::endl;
    while (!lq.empty()) {
        char parent_c, leftChild_c, rightChild_c;
        parent_c = lq.pop();
        leftChild_c = toPrint.leftChild(parent_c, flag);
        rightChild_c = toPrint.rightChild(parent_c, flag);
        std::cout << parent_c << ' ' << leftChild_c << ' ' << rightChild_c << std::endl;
        if (leftChild_c != flag)
            lq.push(leftChild_c);
        if (rightChild_c != flag)
            lq.push(rightChild_c);
    }
}

template <typename Type>
typename linkedBinaryTree<Type>::node* linkedBinaryTree<Type>::find(Type toFind, linkedBinaryTree<Type>::node* toSearch) const {
    node* result;
    if (toSearch == nullptr)
        return nullptr;
    if (toSearch -> data == toFind)
        return toSearch;
    if ((result = find(toFind, toSearch -> leftNode)))
        return result;
    else
        return find(toFind, toSearch -> rightNode);
}

template <typename Type>
void linkedBinaryTree<Type>::preorderTraverse(linkedBinaryTree<Type>::node* toTraverse) const {
    if (toTraverse == nullptr)
        return;
    std::cout << toTraverse -> data << ' ';
    preorderTraverse(toTraverse -> leftNode);
    preorderTraverse(toTraverse -> rightNode);
}

template <typename Type>
void linkedBinaryTree<Type>::inorderTraverse(linkedBinaryTree<Type>::node* toTraverse) const {
    if (toTraverse == nullptr)
        return;
    inorderTraverse(toTraverse -> leftNode);
    std::cout << toTraverse -> data << ' ';
    inorderTraverse(toTraverse -> rightNode);
}

template <typename Type>
void linkedBinaryTree<Type>::postorderTraverse(linkedBinaryTree<Type>::node* toTraverse) const {
    if (toTraverse == nullptr)
        return;
    postorderTraverse(toTraverse -> leftNode);
    postorderTraverse(toTraverse -> rightNode);
    std::cout << toTraverse -> data << ' ';
}

template <typename Type>
void linkedBinaryTree<Type>::clear(linkedBinaryTree<Type>::node*& toClear) {
    if (toClear == nullptr)
        return;
    clear(toClear -> leftNode);
    clear(toClear -> rightNode);
    delete toClear;
    toClear = nullptr;
}

template <typename Type>
linkedBinaryTree<Type>::~linkedBinaryTree() {
    clear(rootNode);
}

template <typename Type>
void linkedBinaryTree<Type>::clear() {
    clear(rootNode);
}

template <typename Type>
void linkedBinaryTree<Type>::create(Type flag) {
    linkedQueue<node*> lq;
    node* toInput;
    Type rootData, leftData, rightData;
    std::cout << "Input the root node: " << std::flush;
    std::cin >> rootData;
    rootNode = new node(rootData);
    lq.push(rootNode);
    while (!lq.empty()) {
        toInput = lq.pop();
        std::cout << "Input the two children of the \"" << toInput -> data << "\", while \"" << flag << "\" means an empty node: " << std::flush;
        std::cin >> leftData >> rightData;
        if (leftData != flag)
            lq.push(toInput -> leftNode = new node(leftData));
        if (rightData != flag)
            lq.push(toInput -> rightNode = new node(rightData));
    }
    std::cout << "The tree is created completely." << std::endl;
}

template <typename Type>
void linkedBinaryTree<Type>::deleteLeft(Type target) {
    node* toDelete = find(target, rootNode);
    if (toDelete == nullptr)
        return;
    clear(toDelete -> leftNode);
}

template <typename Type>
void linkedBinaryTree<Type>::deleteRight(Type target) {
    node* toDelete = find(target, rootNode);
    if (toDelete == nullptr)
        return;
    clear(toDelete -> rightNode);
}

template <typename Type>
void linkedBinaryTree<Type>::preorderTraverse() const {
    std::cout << "\nPreorder Traverse: ";
    preorderTraverse(rootNode);
}

template <typename Type>
void linkedBinaryTree<Type>::inorderTraverse() const {
    std::cout << "\nInorder Traverse: ";
    inorderTraverse(rootNode);
}

template <typename Type>
void linkedBinaryTree<Type>::postorderTraverse() const {
    std::cout << "\nPostorder Traverse: ";
    postorderTraverse(rootNode);
}

template <typename Type>
void linkedBinaryTree<Type>::levelOrderTraverse() const {
    std::cout << "\nLevel Order Traverse: ";
    linkedQueue<node*> lq;
    lq.push(rootNode);
    while (!lq.empty()) {
        node* toOutput = lq.pop();
        std::cout << toOutput -> data << ' ';
        if (toOutput -> leftNode)
            lq.push(toOutput -> leftNode);
        if (toOutput -> rightNode)
            lq.push(toOutput -> rightNode);
    }
}

template <typename Type>
bool linkedBinaryTree<Type>::empty() const {
    return rootNode == nullptr;
}

template <typename Type>
Type linkedBinaryTree<Type>::root(Type flag) const {
    if (rootNode == nullptr)
        return flag;
    else
        return rootNode -> data;
}

template <typename Type>
Type linkedBinaryTree<Type>::leftChild(Type toFind, Type flag) const {
    node* parent = find(toFind, rootNode);
    if (parent == nullptr || parent -> leftNode == nullptr)
        return flag;
    return parent -> leftNode -> data;
}

template <typename Type>
Type linkedBinaryTree<Type>::rightChild(Type toFind, Type flag) const {
    node* parent = find(toFind, rootNode);
    if (parent == nullptr || parent -> rightNode == nullptr)
        return flag;
    return parent -> rightNode -> data;
}
