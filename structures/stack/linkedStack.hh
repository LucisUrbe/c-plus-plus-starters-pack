///
/// @file       linkedStack.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       January 30, 2024
/// @version    0.2
/// @brief      The linked stack class, storing elements in memory chains.
///

#include "stack.hh"

template <typename Type>
class linkedStack: public stack<Type> {
    private:
        struct node {
            Type data;
            node* nextNode;
            node(): nextNode(nullptr) {}
            node(const Type& newData, node* newNextNode = nullptr) {
                data = newData;
                nextNode = newNextNode;
            }
            ~node() {}
        };
        node* topPosition;
    public:
        linkedStack();
        ~linkedStack();
        void push(const Type& toPush);
        Type pop();
        Type top() const;
        bool isEmpty() const;
};

template <typename Type>
linkedStack<Type>::linkedStack() {
    topPosition = nullptr;
}

template <typename Type>
linkedStack<Type>::~linkedStack() {
    node* toDelete;
    while (topPosition != nullptr) {
        toDelete = topPosition;
        topPosition = topPosition -> nextNode;
        delete toDelete;
    }
}

template <typename Type>
void linkedStack<Type>::push(const Type& toPush) {
    topPosition = new node(toPush, topPosition);
}

template <typename Type>
Type linkedStack<Type>::pop() {
    if (isEmpty()) {
        Type* empty = new Type(0);
        return *empty;
    }
    node* toPop = topPosition;
    Type toReturn = toPop -> data;
    topPosition = topPosition -> nextNode;
    delete toPop;
    return toReturn;
}

template <typename Type>
Type linkedStack<Type>::top() const {
    return topPosition -> data;
}

template <typename Type>
bool linkedStack<Type>::isEmpty() const {
    return topPosition == nullptr;
}