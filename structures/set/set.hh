///
/// @file       set.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       April 26, 2024
/// @version    0.2
/// @brief      The father class of all sets and some very basic search methods.
///

template <typename KEY, typename VALUE>
struct SET {
    KEY key;
    VALUE value;
};

template <typename KEY, typename VALUE>
int sequenceSearch(SET<KEY, VALUE> data[], int size, const KEY& toFind) {
    data[0].key = toFind;
    int i;
    for (i = size; toFind != data[i].key; i--);
    return i;
}

template <typename KEY, typename VALUE>
int sequencedSearch(SET<KEY, VALUE> data[], int size, const KEY& toFind) {
    data[0].key = toFind;
    int i;
    for (i = size; toFind < data[i].key; i--);
    if (toFind < data[i].key || i == 0)
        return 0;
    else
        return i;
}

template <typename KEY, typename VALUE>
int binarySearch(SET<KEY, VALUE> data[], int size, const KEY& toFind) {
    int low = 1;
    int high = size;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (toFind == data[mid].key)
            return mid;
        if (toFind < data[mid].key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return 0;
}
