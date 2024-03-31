///
/// @file       linkedQueue.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       March 17, 2024
/// @version    0.2
/// @brief      The priority queue class, storing elements in a heap.
///

template <typename Type>
class priorityQueue {
    private:
        int currentSize;
        int maxSize;
        Type* heap;
        void doubleSpace();
        void percolateDown(int hole);
        void buildHeap();
    public:
        priorityQueue(int capacity = 100);
        priorityQueue(const Type data[], int size);
        ~priorityQueue();
        bool empty() const;
        void push(const Type& toPush);
        Type pop();
        Type top() const;
};

template <typename Type>
void priorityQueue<Type>::doubleSpace() {
    Type* toDelete = heap;
    maxSize *= 2;
    heap = new Type[maxSize];
    for (int i = 0; i < currentSize; i++)
        heap[i] = toDelete[i];
    delete [] toDelete;
}

template <typename Type>
void priorityQueue<Type>::percolateDown(int hole) {
    int child;
    Type toPercolate = heap[hole];
    while (hole * 2 < currentSize) {
        child = hole * 2;
        if (child != currentSize && heap[child + 1] < heap[child])
            child++;
        if (heap[child] < toPercolate)
            heap[hole] = heap[child];
        else
            break;
        hole = child;
    }
    heap[hole] = toPercolate;
}

template <typename Type>
void priorityQueue<Type>::buildHeap() {
    for (int i = currentSize / 2; i > 0; i--)
        percolateDown(i);
}

template <typename Type>
priorityQueue<Type>::priorityQueue(int capacity) {
    heap = new Type[capacity];
    maxSize = capacity;
    currentSize = 0;
}

template <typename Type>
priorityQueue<Type>::priorityQueue(const Type* data, int size): maxSize(size + 10), currentSize(size) {
    heap = new Type[maxSize];
    for (int i = 0; i < size; i++)
        heap[i + 1] = data[i];
    buildHeap();
}

template <typename Type>
priorityQueue<Type>::~priorityQueue() {
    delete [] heap;
}

template <typename Type>
bool priorityQueue<Type>::empty() const {
    return currentSize == 0;
}

template <typename Type>
Type priorityQueue<Type>::top() const {
    return heap[1];
}

template <typename Type>
void priorityQueue<Type>::push(const Type& toPush) {
    if (currentSize == maxSize - 1)
        doubleSpace();
    int hole;
    for (hole = ++currentSize; hole > 1 && toPush < heap[hole / 2]; hole /= 2)
        heap[hole] = heap[hole / 2];
    heap[hole] = toPush;
}

template <typename Type>
Type priorityQueue<Type>::pop() {
    Type toReturn = heap[1];
    heap[1] = heap[currentSize--];
    percolateDown(1);
    return toReturn;
}
