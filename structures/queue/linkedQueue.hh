///
/// @file       linkedQueue.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       March 14, 2024
/// @version    0.2
/// @brief      The linked queue class, storing elements in memory chains.
///

#include "queue.hh"

template <typename Type>
class linkedQueue: public queue<Type> {
    private:
        struct node {
            Type data;
            node* next;
            node(const Type& newData, node* newNode = nullptr) {
                data = newData;
                next = newNode;
            }
            node(): next(nullptr) {}
            ~node() {}
        };
        node* head;
        node* tail;
    public:
        linkedQueue();
        ~linkedQueue();
        void push(const Type& toPush);
        Type pop();
        Type front() const;
        Type back() const;
        bool empty() const;
};

template <typename Type>
linkedQueue<Type>::linkedQueue() {
    head = tail = nullptr;
}

template <typename Type>
linkedQueue<Type>::~linkedQueue() {
    node* toDelete;
    while (head != nullptr) {
        toDelete = head;
        head = head -> next;
        delete toDelete;
    }
}

template <typename Type>
void linkedQueue<Type>::push(const Type& toPush) {
    if (tail == nullptr)
        head = tail = new node(toPush);
    else
        tail = tail -> next = new node(toPush);
}

template <typename Type>
Type linkedQueue<Type>::pop() {
    node* toDelete = head;
    Type toReturn = head -> data;
    head = head -> next;
    if (head == nullptr)
        tail = nullptr;
    delete toDelete;
    return toReturn;
}

template <typename Type>
Type linkedQueue<Type>::front() const {
    return head -> data;
}

template <typename Type>
Type linkedQueue<Type>::back() const {
    return tail -> data;
}

template <typename Type>
bool linkedQueue<Type>::empty() const {
    return head == nullptr;
}
