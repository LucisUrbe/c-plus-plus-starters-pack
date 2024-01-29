///
/// @file       linearList.hh
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       January 29, 2024
/// @version    0.2
/// @brief      The sequence stack class, storing elements in continuous memory space.
///

#include "stack.hh"

template <typename Type>
class sequenceStack: public stack<Type> {
private:
    int topPosition;
    int maxSize;
    Type* element;
    void doubleSpace();
public:
    sequenceStack(int initialSize = 10);
    ~sequenceStack();
    void push(const Type& toPush);
    Type pop();
    Type top() const;
    bool isEmpty() const;
};

template <typename Type>
void sequenceStack<Type>::doubleSpace() {
    Type* source = element;
    element = new Type[maxSize * 2];
    for (int i = 0; i < maxSize; i++)
        element[i] = source[i];
    maxSize *= 2;
    delete [] source;
}

template <typename Type>
sequenceStack<Type>::sequenceStack(int initialSize) {
    element = new Type[initialSize];
    maxSize = initialSize;
    topPosition = -1;
}

template <typename Type>
sequenceStack<Type>::~sequenceStack() {
    delete [] element;
}

template <typename Type>
void sequenceStack<Type>::push(const Type& toPush) {
    if (topPosition == maxSize - 1)
        doubleSpace();
    element[++topPosition] = toPush;
}

template <typename Type>
Type sequenceStack<Type>::pop() {
    if (isEmpty()) {
        Type* empty = nullptr;
        return *empty;
    } // Considering robustness
    return element[topPosition--];
}

template <typename Type>
Type sequenceStack<Type>::top() const {
    return element[topPosition];
}

template <typename Type>
bool sequenceStack<Type>::isEmpty() const {
    return topPosition == -1;
}
