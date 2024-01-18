///
/// @file       sequanceList.hh
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       January 18, 2024
/// @version    0.3
/// @brief      The sequence list class, storing elements in continuous memory space.
///

#include "linearList.hh"

template<typename Type>
class sequenceList: public linearList<Type> {
    private:
        Type* data;
        int currentLength;
        int maxSize;
        void doubleSpace(); //double the space of the array
    public:
        sequenceList(int initialSize = 16);
        ~sequenceList();
        void insert(int position, const Type &x);
        void remove(int position);
        void clear();
        void traverse() const;
        int length() const;
        int search(const Type &x) const;
        Type visit(int position) const;
};

template<typename Type>
sequenceList<Type>::sequenceList(int initialSize) {
    data = new Type[initialSize];
    maxSize = initialSize;
    currentLength = 0;
}

template<typename Type>
sequenceList<Type>::~sequenceList() {
    delete[] data;
}

template<typename Type>
void sequenceList<Type>::insert(int position, const Type &x) {
    if (currentLength == maxSize)
        doubleSpace();
    for (int i = currentLength; i > position; i--)
        data[i] = data[i - 1];
    data[position] = x;
    currentLength++;
}

template<typename Type>
void sequenceList<Type>::remove(int position) {
    for (int i = position; i < currentLength - 1; i++)
        data[i] = data[i + 1];
    currentLength--;
}

template<typename Type>
void sequenceList<Type>::clear() {
    currentLength = 0;
}

template<typename Type>
void sequenceList<Type>::traverse() const {
    std::cout << std::endl;
    for (int i = 0; i < currentLength; i++)
        std::cout << data[i] << ' ';
}

template<typename Type>
int sequenceList<Type>::length() const {
    return currentLength;
}

template<typename Type>
int sequenceList<Type>::search(const Type &x) const {
    int i;
    for (i = 0; i < currentLength && data[i] != x; i++);
    if (i == currentLength)
        return -1;
    else
        return i;
}

template<typename Type>
Type sequenceList<Type>::visit(int position) const {
    return data[position];
}

template<typename Type>
void sequenceList<Type>::doubleSpace() {
    Type* tmp = data;
    maxSize *= 2;
    data = new Type[maxSize];
    for (int i = 0; i < currentLength; i++)
        data[i] = tmp[i];
    delete[] tmp;
}
