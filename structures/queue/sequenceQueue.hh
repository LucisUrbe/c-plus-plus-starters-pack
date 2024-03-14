///
/// @file       sequenceQueue.hh
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       February 10, 2024
/// @version    0.2
/// @brief      The sequence queue class, storing elements in continuous memory space.
///

#include "queue.hh"

template <typename Type>
class sequenceQueue: public queue<Type> {
    private:
        Type* data;
        int maxSize, head, tail;
        void doubleSpace();
    public:
        sequenceQueue(int size = 10);
        ~sequenceQueue();
        void push(const Type& toPush);
        Type pop();
        Type front() const;
        bool empty() const;
};

template <typename Type>
void sequenceQueue<Type>::doubleSpace() {
    Type* source = data;
    data = new Type[maxSize * 2];
    for (int i = 1; i < maxSize; i++)
        data[i] = source[(head + i) % maxSize];
    head = 0;
    tail = maxSize - 1;
    maxSize *= 2;
    delete source;
}

template <typename Type>
sequenceQueue<Type>::sequenceQueue(int size) {
    data = new Type[size];
    maxSize = size;
    head = tail = 0;
}

template <typename Type>
sequenceQueue<Type>::~sequenceQueue() {
    delete [] data;
}

template <typename Type>
void sequenceQueue<Type>::push(const Type& toPush) {
    if ((tail + 1) % maxSize == head)
        doubleSpace();
    tail = (tail + 1) % maxSize;
    data[tail] = toPush;
}

template <typename Type>
Type sequenceQueue<Type>::pop() {
    head = (head + 1) % maxSize;
    return data[head];
}

template <typename Type>
Type sequenceQueue<Type>::front() const {
    return data[(head + 1) % maxSize];
}

template <typename Type>
bool sequenceQueue<Type>::empty() const {
    return head == tail;
}
