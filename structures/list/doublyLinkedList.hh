///
/// @file       doublyLinkedList.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       January 19, 2024
/// @version    0.3
/// @brief      The doubly linked list class, storing elements in memory chains.
///

#if !defined(_LIBCPP_IOSTREAM) || !defined(_GLIBCXX_IOSTREAM)
    #include <iostream>
#endif
#include "linearList.hh"

template<typename Type>
class doublyLinkedList: public linearList<Type> {
    private:
        struct node {
            Type data;
            node* previous, * next;
            node(const Type &rawData, node* previousNode = nullptr, node* nextNode = nullptr) {
                data = rawData;
                previous = previousNode;
                next = nextNode;
            }
            node(): previous(nullptr), next(nullptr) {}
            ~node() {}
        };
        int currentLength;
        node* head, * tail;
        node* where(int position) const;
    public:
        doublyLinkedList();
        ~doublyLinkedList() {
            clear();
            delete head;
            delete tail; // note that there is NO delete head, tail;
        }
        void insert(int position, const Type &rawData);
        void remove(int position);
        void clear();
        void traverse() const;
        int length() const {
            return currentLength;
        }
        int search(const Type &toFind) const;
        Type visit(int position) const;
};

template<typename Type>
doublyLinkedList<Type>::doublyLinkedList() {
    head = new node;
    head -> next = tail = new node;
    tail -> previous = head;
    currentLength = 0;
}

template<typename Type>
typename doublyLinkedList<Type>::node* doublyLinkedList<Type>::where(int position) const {
    node* target = head;
    while (position-- >= 0)
        target = target -> next;
    return target;
}

template<typename Type>
void doublyLinkedList<Type>::insert(int position, const Type &rawData) {
    node* toInsert, * newData;
    toInsert = where(position);
    newData = new node(rawData, toInsert -> previous, toInsert);
    toInsert -> previous -> next = newData;
    toInsert -> previous = newData;
    currentLength++;
}

template<typename Type>
void doublyLinkedList<Type>::remove(int position) {
    node* toRemove;
    toRemove = where(position);
    toRemove -> previous -> next = toRemove -> next;
    toRemove -> next -> previous = toRemove -> previous;
    delete toRemove;
    currentLength--;
}

template<typename Type>
void doublyLinkedList<Type>::clear() {
    node* toDelete = head -> next, * nextDelete;
    head -> next = tail;
    tail -> previous = head;
    while (toDelete != tail) {
        nextDelete = toDelete -> next;
        delete toDelete;
        toDelete = nextDelete;
    }
    currentLength = 0;
}

template<typename Type>
void doublyLinkedList<Type>::traverse() const {
    node* toShow = head -> next;
    std::cout << std::endl;
    while (toShow != tail) {
        std::cout << toShow -> data << ' ';
        toShow = toShow -> next;
    }
    std::cout << std::endl;
}

template<typename Type>
int doublyLinkedList<Type>::search(const Type &toFind) const {
    int position;
    node* toCompare = head -> next;
    for (position = 0; toCompare != tail && toCompare -> data != toFind; position++)
        toCompare = toCompare -> next;
    if (toCompare == tail)
        return -1;
    else
        return position;
}

template<typename Type>
Type doublyLinkedList<Type>::visit(int position) const {
    return where(position) -> data;
}
