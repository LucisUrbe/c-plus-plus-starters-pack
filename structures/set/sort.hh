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

// the up-down-divide function of the quick sort according to the pivot(low)
template <typename KEY, typename VALUE>
int divide(SET<KEY, VALUE>*& toDivide, int low, int high) {
    SET<KEY, VALUE> standard = toDivide[low];
    do {
        while (low < high && toDivide[high].key >= standard.key)
            high--; // from high to low, find the first element smaller than the pivot
        if (low < high) {
            // covering the low with the high, the first one covered is "standard",
            // the second one being the empty place from the last large loop
            toDivide[low] = toDivide[high];
            low++;
        }
        while (low < high && toDivide[low].key <= standard.key)
            low++; // check from low to high until the first element bigger than the pivot is met
        if (low < high) {
            // covering the high with the low, the first one covered is the empty place from the last small loop
            toDivide[high] = toDivide[low];
            high--;
        }
    } while (low != high);
    toDivide[low] = standard; // low == high, which is the place that the pivot should be
    return low;
}
// the actual quick sort function
template <typename KEY, typename VALUE>
void quickSort(SET<KEY, VALUE>*& toSort, int low, int high) {
    if (low >= high)
        return;
    int mid = divide(toSort, low, high);
    quickSort(toSort, low, mid - 1); // the "mid" element is at the right place; now sort the remaining ones
    quickSort(toSort, mid + 1, high);
}
// Quick sort: O(n*lb(n))~(n^2)
template <typename KEY, typename VALUE>
void quickSort(SET<KEY, VALUE>*& toSort, int size) {
    quickSort(toSort, 0, size - 1);
}


// the merge function of merge sort; Note that what to be merged are the two organized halves of a list
template <typename KEY, typename VALUE>
void merge(SET<KEY, VALUE>*& toMerge, int left, int mid, int right) {
    SET<KEY, VALUE>* result = new SET<KEY, VALUE>[right - left + 1];
    // i for the left half (left ~ mid-1), j for the right half (mid ~ right), k for the result (left ~ right)
    int i = left, j = mid, k = 0;
    while (i < mid && j <= right)
        if (toMerge[i].key < toMerge[j].key)
            result[k++] = toMerge[i++]; // The smaller one goes into the result
        else
            result[k++] = toMerge[j++];
    while (i < mid) // Directly merge the remaining of the left half
        result[k++] = toMerge[i++];
    while (j <= right) // The right half
        result[k++] = toMerge[j++];
    for (int i = 0, j = left; j <= right; i++, j++)
        toMerge[j] = result[i]; // give back the result
    delete [] result;
}
// the actual function of merge sort
template <typename KEY, typename VALUE>
void mergeSort(SET<KEY, VALUE>*& toSort, int left, int right) {
    if (left == right)
        return;
    int mid = (left + right) / 2;
    mergeSort(toSort, left, mid);
    mergeSort(toSort, mid + 1, right);
    merge(toSort, left, mid + 1, right);
}
// Merge sort: O(n*lb(n))
template <typename KEY, typename VALUE>
void mergeSort(SET<KEY, VALUE>*& toSort, int size) {
    mergeSort(toSort, 0, size - 1);
}

// Integer bucket sort: O(n*carry)
// Assuming that the keys are decimal integers
template <typename KEY, typename VALUE>
void bucketSort(SET<KEY, VALUE>*& toSort, int size) {
    struct setNode {
        SET<KEY, VALUE> data;
        setNode* next;
        setNode(): next(nullptr) {}
        setNode(SET<KEY, VALUE>& rawData, setNode* rawNode): data(rawData), next(rawNode) {} // KEY must be int
        ~setNode() {}
    };
    // new feature: convert toSort to actualList
    setNode* actualList = nullptr;
    for (int i = 0; i < size; i++)
        actualList = new setNode(toSort[size - 1 - i], actualList); // this behaves like a stack
    // the following algorithm will find the maximum number of digits for a key
    int max = 0;
    for (setNode* tail = actualList; tail != nullptr; tail = tail -> next)
        if (tail -> data.key > max)
            max = tail -> data.key;
    int carry = 0;
    if (max != 0)
        while (max > 0) {
            carry++;
            max /= 10;
        }
    // the actual algorithm is as follows
    for (int i = 1, base = 1; i < carry; i++, base *= 10) {
        setNode* first[10], *last[10];
        for (int j = 0; j < 10; j++)
            first[j] = last[j] = nullptr; // initialize the bucket
        while (actualList != nullptr) {
            int position = actualList -> data.key / base % 10; // find which bucket the node goes to
            if (first[position] == nullptr)
                first[position] = last[position] = actualList;
            else
                last[position] = last[position] -> next = actualList;
            actualList = actualList -> next;
        }
        setNode* tail = nullptr;
        for (int j = 0; j < 10; j++) {
            if (first[j] == nullptr)
                continue;
            if (tail == nullptr)
                actualList = tail = first[j];
            else
                tail -> next = first[j];
            tail = last[j];
        }
        tail -> next = nullptr;
    }
    // convert actualList to toSort
    for (int i = 0; i < size; i++) {
        toSort[i] = actualList -> data;
        actualList = actualList -> next;
    }
}
