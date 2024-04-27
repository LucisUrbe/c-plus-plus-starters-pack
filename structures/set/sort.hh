///
/// @file       sort.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       April 27, 2024
/// @version    0.2
/// @brief      Some classic method to sort SETs according to the KEYs.
///

#include "set.hh"

// Direct insertion sort: compare current element with all the elements on the left, from left to right; O(n^2)
template <typename KEY, typename VALUE>
void directInsertionSort(SET<KEY, VALUE>*& toSort, int size) {
    for (int i = 0, j; i < size; i++) {
        SET<KEY, VALUE> toInsert = toSort[i];
        for (j = i - 1; j >= 0 && toInsert.key < toSort[j].key; j--)
            toSort[j + 1] = toSort[j];
        toSort[j + 1] = toInsert;
    }
}

// Binary insertion sort: comparison-with-left process is replaced with binary search; O(n^2)

// Shell sort: the "step" is halved every iteration, from left to right, using direct insertion sort but only comparing
// elements with distance of "step"; The "step" is initialized with half of the size of the sets; O(n^1.25)~(n^2)
template <typename KEY, typename VALUE>
void ShellSort(SET<KEY, VALUE>*& toSort, int size) {
    for (int step = size / 2; step > 0; step /= 2)
        for (int i = step, j; i < size; i++) {
            SET<KEY, VALUE> toInsert = toSort[i];
            for (j = i - step; j >= 0 && toInsert.key < toSort[j].key; j -= step)
                toSort[j + step] = toSort[j];
            toSort[j + step] = toInsert;
        }
}

// Direct selection sort: from the i-th element,
// find the minimal element on the right and swap it with the i-th element; O(n^2)
template <typename KEY, typename VALUE>
void directSelectionSort(SET<KEY, VALUE>*& toSort, int size) {
    // Note that this i-th element can lastly be penultimate, otherwise the search process out of bound
    for (int i = 0; i < size - 1; i++) {
        int min_P = i;
        for (int j = i + 1; j < size; j++)
            if (toSort[j].key < toSort[min_P].key)
                min_P = j;
        SET<KEY, VALUE> toSwap = toSort[i];
        toSort[i] = toSort[min_P];
        toSort[min_P] = toSwap;
    }
}

// the percolate-down function of heap sort
template <typename KEY, typename VALUE>
void percolateDown(SET<KEY, VALUE>*& toPercolate, int hole, int size) {
    // The "hole" could be 0;
    // Note that in a priority queue the "hole" could the least be 1
    SET<KEY, VALUE> toCompare = toPercolate[hole];
    for (int child; hole * 2 + 1 < size; hole = child) {
        // The child node in a heap is at twice of "hole"(position/index) plus one;
        // When creating a heap, the first "hole" is the one before the medium,
        // and child = size - 1, which is the tail element
        child = hole * 2 + 1;
        // If not the last element, the selected child is the bigger one of the two;
        // Note that in a priority queue the selected child is the smaller one
        if (child != size - 1 && toPercolate[child + 1].key > toPercolate[child].key)
            child++;
        // If the child node is bigger than the "hole" value, put the child in the "hole", and percolate from the child;
        // else break the loop
        if (toPercolate[child].key > toCompare.key)
            toPercolate[hole] = toPercolate[child];
        else
            break;
    }
    toPercolate[hole] = toCompare;
}
// Heap sort: O(n*lb(n))
template <typename KEY, typename VALUE>
void heapSort(SET<KEY, VALUE>*& toSort, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        percolateDown(toSort, i, size);
    for (int i = size - 1; i > 0; i--) {
        SET<KEY, VALUE> space = toSort[0];
        toSort[0] = toSort[i];
        toSort[i] = space;
        percolateDown(toSort, 0, i);
    }
}

// Bubble swap function: O(n^2)
template <typename KEY, typename VALUE>
void bubbleSort(SET<KEY, VALUE>*& toSort, int size) {
    bool unfinished = true;
    for (int i = 1; i < size && unfinished; i++) {
        unfinished = false; // If the process below swaps nothing, break the loop
        for (int j = 0; j < size - i; j++)
            if (toSort[j + 1].key < toSort[j].key) { // If the current element is bigger, let it go right
                SET<KEY, VALUE> toSwap = toSort[j];
                toSort[j] = toSort[j + 1];
                toSort[j + 1] = toSwap;
                unfinished = true;
            }
    }
}
