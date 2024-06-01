///
/// @file       openHashTable.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       June 1, 2024
/// @version    0.2
/// @brief      The open hash table, solving the dictionary problem with buckets.
///

#include "dynamicSearchTable.hh"

template <typename KEY, typename VALUE>
class openHashTable: public dynamicSearchTable<KEY, VALUE> {
private:
    struct node {
        SET<KEY, VALUE> data;
        node* next;
        node() {
            next = nullptr;
        }
        node(const SET<KEY, VALUE>& rawData, node* rawNode): data(rawData), next(rawNode) {}
    };
    node** array;
    int size;
    int (*key)(const KEY& toConvert);
    static int defaultKey(const int& toConvert) {
        return toConvert;
    }
public:
    openHashTable(int length = 101, int (*function)(const KEY& toConvert) = defaultKey);
    ~openHashTable();
    SET<KEY, VALUE>* find(const KEY& toFind) const;
    void insert(const SET<KEY, VALUE>& toInsert);
    void remove(const KEY& toRemove);
};

template <typename KEY, typename VALUE>
openHashTable<KEY, VALUE>::openHashTable(int length, int (*function)(const KEY& toConvert)) {
    size = length;
    array = new node*[size];
    key = function;
    for (int i = 0; i < size; i++)
        array[i] = nullptr;
}

template <typename KEY, typename VALUE>
openHashTable<KEY, VALUE>::~openHashTable() {
    node* toDelete, * nextDelete;
    for (int i = 0; i < size; i++) {
        toDelete = array[i]; // Here, memory may be leaked
        while (toDelete != nullptr) {
            nextDelete = toDelete -> next;
            delete toDelete;
            toDelete = nextDelete;
        }
        delete [] array;
    }
}

template <typename KEY, typename VALUE>
void openHashTable<KEY, VALUE>::insert(const SET<KEY, VALUE>& toInsert) {
    int position = key(toInsert.key) % size;
    array[position] = new node(toInsert, array[position]);
}

template <typename KEY, typename VALUE>
void openHashTable<KEY, VALUE>::remove(const KEY& toRemove) {
    int position = key(toRemove) % size;
    if (array[position] == nullptr)
        return;
    node* current = array[position];
    if (array[position] -> data.key == toRemove) {
        array[position] = current -> next;
        delete current;
        return;
    }
    while (current -> next != nullptr && current -> next -> data.key != toRemove)
        current = current -> next;
    if (current -> next != nullptr) {
        node* toDelete = current -> next;
        current -> next = toDelete -> next;
        delete toDelete;
    }
}

template <typename KEY, typename VALUE>
SET<KEY, VALUE>* openHashTable<KEY, VALUE>::find(const KEY& toFind) const {
    int position = key(toFind) % size;
    node* result = array[position];
    while (result != nullptr && result -> data.key != toFind)
        result = result -> next;
    if (result == nullptr)
        return nullptr;
    else
        return (SET<KEY, VALUE>*) result;
}
