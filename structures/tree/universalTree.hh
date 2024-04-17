///
/// @file       universalTree.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       April 17, 2024
/// @version    0.2
/// @brief      Calculate a universal tree (a tree with multiple branches) using a linked binary tree.
///

// If the definition from clang, gcc and msvc for iostream is not found, include it.
#if !defined(_LIBCPP_IOSTREAM) || !defined(_GLIBCXX_IOSTREAM) || !defined(_IOSTREAM_)
#include <iostream>
#endif
#include "../queue/linkedQueue.hh"
#include "../stack/linkedStack.hh"

template <typename Type>
class universalTree {
private:
    struct node {
        Type data;
        node* firstSon;
        node* nextSibling;
        node(): firstSon(nullptr), nextSibling(nullptr) {}
        node(Type rawData, node* son = nullptr, node* sibling = nullptr): data(rawData), firstSon(son), nextSibling(sibling) {}
        ~node() {}
    };
    node* rootNode;
    Type flag;
    void clear(node*& toClear) {
        if (toClear == nullptr)
            return;
        clear(toClear -> firstSon);
        clear(toClear -> nextSibling);
        delete toClear;
        toClear = nullptr;
    }
    bool find(node* toSearch, Type toFind, linkedStack<bool>& position) const {
        if (toSearch == nullptr)
            return false;
        if (toSearch -> data == toFind)
            return true;
        if (find(toSearch -> firstSon, toFind, position)) {
            position.push(0);
            return true;
        }
        if (find(toSearch -> nextSibling, toFind, position)) {
            position.push(1);
            return true;
        }
        return false;
    }
public:
    universalTree(): rootNode(nullptr) {}
    universalTree(Type rawData) {
        rootNode = new node(rawData);
    }
    ~universalTree() {
        // clear(); // It will ruin the list !!! !!! !!!
    }
    void clear() {
        clear(rootNode);
    }
    void create() {
        std::cout << "We need a specific value to represent that you do not want to insert the node at the place. \nThis value should be the same type but never appear in your data: " << std::flush;
        std::cin >> flag;
        std::cout << "No problem! Next, input the data of the root node:" << std::flush;
        Type rootData;
        std::cin >> rootData;
        rootNode = new node(rootData);
        linkedQueue<node*> lq;
        lq.push(rootNode);
        while (!lq.empty()) {
            node* toInput = lq.pop();
            std::cout << "\nNote: you can input \"" << flag << "\"to represent that you do not want a node at this place." << std::endl;
            std::cout << "Input the data of the first child node of the node " << toInput -> data << ":" << std::flush;
            Type firstSonData;
            std::cin >> firstSonData;
            if (firstSonData != flag)
                lq.push(toInput -> firstSon = new node(firstSonData));
            if (toInput == rootNode)
                continue;
            std::cout << "OK! Then, input the data of the next child node of the node " << toInput -> data << ":" << std::flush;
            Type nextSiblingData;
            std::cin >> nextSiblingData;
            if (nextSiblingData != flag)
                lq.push(toInput -> nextSibling = new node(nextSiblingData));
        }
        std::cout << "Great! By doing this, a tree is planted!" << std::endl;
    }
    bool empty() const {
        return rootNode == nullptr;
    }
    bool find(Type toFind) const {
        linkedStack<bool> position;
        if (find(rootNode, toFind, position)) {
            std::cout << "\nFound data: " << toFind << std::endl;
            node* current = rootNode;
            std::cout << "Path: " << current -> data << std::flush;
            while (!position.isEmpty()) {
                if (position.pop()) { // to the right
                    current = current -> nextSibling;
                    while (!position.isEmpty() && position.top()) {
                        current = current -> nextSibling;
                        position.pop();
                    }
                    std::cout << " -- " << current -> data << std::flush;
                }
                else { // to the left
                    current = current -> firstSon;
                    if (position.isEmpty() || !position.top())
                        std::cout << " -- " << current -> data << std::flush;
                }
            }
            std::cout << std::endl;
            return true;
        }
        else
            return false;
    }
};
