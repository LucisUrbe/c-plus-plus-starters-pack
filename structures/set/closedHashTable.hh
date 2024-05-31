///
/// @file       closedHashTable.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       May 31, 2024
/// @version    0.2
/// @brief      The closed hash table, solving the dictionary problem with linear probing.
///

#include "dynamicSearchTable.hh"

template <typename KEY, typename VALUE>
class closedHashTable: public dynamicSearchTable<KEY, VALUE> {
private:
    struct node {
        SET<KEY, VALUE> data;
        short state; // 0: empty, 1: active, 2: deleted
        node(): state(0) {}
    };
    node* array;
    int size;
    int (*key)(const KEY& toConvert); // if the key is not int, the user must provide a function to convert it to int
    static int defaultKey(const int& toConvert) {
        return toConvert;
    }
public:
    closedHashTable(int defaultLength = 101, int (*function)(const KEY& toConvert) = defaultKey);
    ~closedHashTable() {
        delete [] array;
    }
    SET<KEY, VALUE>* find(const KEY& toFind) const;
    void insert(const SET<KEY, VALUE>& toInsert);
    void remove(const KEY& toRemove);
};

template <typename KEY, typename VALUE>
closedHashTable<KEY, VALUE>::closedHashTable(int defaultLength, int (*function)(const KEY& toConvert)) {
    size = defaultLength;
    array = new node[size];
    key = function;
}

template <typename KEY, typename VALUE>
void closedHashTable<KEY, VALUE>::insert(const SET<KEY, VALUE>& toInsert) {
    int initialPosition, position;
    initialPosition = position = key(toInsert.key) % size;
    do {
        if (array[position].state != 1) {
            array[position].data = toInsert;
            array[position].state = 1;
            return;
        }
        position = (position + 1) % size;
    } while (position != initialPosition);
}

template <typename KEY, typename VALUE>
void closedHashTable<KEY, VALUE>::remove(const KEY& toRemove) {
    int initialPosition, position;
    initialPosition = position = key(toRemove) % size;
    do {
        if (array[position].state == 0)
            return;
        if (array[position].state == 1 && array[position].data.key == toRemove) {
            array[position].state = 2;
            return;
        }
        position = (position + 1) % size;
    } while (position != initialPosition);
}

template <typename KEY, typename VALUE>
SET<KEY, VALUE>* closedHashTable<KEY, VALUE>::find(const KEY& toFind) const {
    int initialPosition, position;
    initialPosition = position = key(toFind) % size;
    do {
        if (array[position].state == 0)
            return nullptr;
        if (array[position].state == 1 && array[position].data.key == toFind)
            return (SET<KEY, VALUE>*) &array[position]; // !!! 将类截短成SET？ !!!
        position = (position + 1) % size;
    } while (position != initialPosition);
}
