///
/// @file       singlyLinkedList.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       January 19, 2024
/// @version    0.3
/// @brief      The singly linked list class, storing elements in memory chains.
///

#if !defined(_LIBCPP_IOSTREAM) || !defined(_GLIBCXX_IOSTREAM)
    #include <iostream>
#endif
#include "linearList.hh"

template<typename Type>
class singlyLinkedList: public linearList<Type> {
    private:
        struct node {
            Type data;
            node* next;
            node(const Type &rawData, node* nextNode = nullptr) {
                data = rawData;
                next = nextNode;
            }
            node(): next(nullptr) {}
            ~node() {}
        };
        int currentLength;
        node* head;
        node* where(int position) const; // returns the address of the position node

    public:
        singlyLinkedList();
        ~singlyLinkedList() {
            clear();
            delete head;
        }
        void insert(int position, const Type &rawData);
        void remove(int position);
        void clear();
        void traverse() const;
        int length() const {
            return currentLength;
        }
        int search(const Type &x) const;
        Type visit(int position) const;
};

template<typename Type>
typename singlyLinkedList<Type>::node* singlyLinkedList<Type>::where(int postition) const {
    node *p = head;
    while (postition-- >= 0)
        p = p -> next;
    return p;
}

template<typename Type>
singlyLinkedList<Type>::singlyLinkedList() {
    head = new node;
    currentLength = 0;
}

template<typename Type>
void singlyLinkedList<Type>::insert(int position, const Type &rawData) {
    node* toInsert;
    toInsert = where(position - 1);
    toInsert -> next = new node(rawData, toInsert -> next);
    currentLength++;
}

template<typename Type>
void singlyLinkedList<Type>::remove(int position) {
    node* beforeRemove, * toRemove;
    beforeRemove = where(position - 1);
    toRemove = beforeRemove -> next;
    beforeRemove -> next = toRemove -> next;
    delete toRemove;
    currentLength--;
}

template<typename Type>
void singlyLinkedList<Type>::clear() {
    node *toDelete = head -> next, * nextDelete;
    head -> next = nullptr;
    while (toDelete != nullptr) {
        nextDelete = toDelete -> next;
        delete toDelete;
        toDelete = nextDelete;
    }
    currentLength = 0;
}

template<typename Type>
void singlyLinkedList<Type>::traverse() const {
    node* toShow = head -> next;
    std::cout << std::endl;
    while (toShow != nullptr) {
        std::cout << toShow -> data << ' ';
        toShow = toShow -> next;
    }
    std::cout << std::endl;
}

template<typename Type>
int singlyLinkedList<Type>::search(const Type &toFind) const {
    node* toCompare = head -> next;
    int position = 0;
    while (toCompare != nullptr && toCompare -> data != toFind) {
        toCompare = toCompare -> next;
        position++;
    }
    if (toCompare == nullptr)
        return -1; // not found
    else
        return position;
}

template<typename Type>
Type singlyLinkedList<Type>::visit(int position) const {
    return where(position) -> data;
}
