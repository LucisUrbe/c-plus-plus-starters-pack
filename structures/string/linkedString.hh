///
/// @file       linkedString.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       March 19, 2024
/// @version    0.2
/// @brief      The linked string class, storing a string in a singly linked list.
///

#if !defined(_LIBCPP_IOSTREAM) || !defined(_GLIBCXX_IOSTREAM) || !defined(_IOSTREAM_)
    #include <iostream>
#endif
#if !defined(_LIBCPP_CMATH) || !defined(_GLIBCXX_CMATH) || !defined(_CMATH_)
    #include <cmath>
#endif

class linkedString {
    private:
        friend linkedString operator+(const linkedString& s1, const linkedString& s2);
        friend bool operator>(const linkedString& s1, const linkedString& s2);
        friend bool operator<(const linkedString& s1, const linkedString& s2);
        friend bool operator==(const linkedString& s1, const linkedString& s2);
        friend bool operator!=(const linkedString& s1, const linkedString& s2);
        friend bool operator>=(const linkedString& s1, const linkedString& s2);
        friend bool operator<=(const linkedString& s1, const linkedString& s2);
        friend std::ostream& operator<<(std::ostream& os, const linkedString& s);
        struct node {
            int size;
            char* data;
            node* next;
            node(int cellSize = 1, node* nextNode = nullptr) {
                data = new char[cellSize];
                size = 0;
                next = nextNode;
            }
            ~node() {}
        };
        node* head;
        int nodeSize;
        int stringLength;
        void clear();
        void findPosition(int startPosition, int& position, node*& address) const;
        void split(node* toSplit, int position);
        void merge(node* toMerge);
    public:
        linkedString(const char* source = "");
        linkedString(const linkedString& source);
        ~linkedString();
        linkedString& operator=(const linkedString& source);
        linkedString substr(int startPosition, int substringLength) const;
        int length() const;
        void insert(int startPosition, const linkedString& source);
        void remove(int startPosition, int removeLength);
};


void linkedString::clear() {
    node* toDelete = head -> next;
    node* nextDelete;
    while (toDelete) {
        nextDelete = toDelete -> next;
        delete toDelete;
        toDelete = nextDelete;
    }
}

void linkedString::findPosition(int startPosition, int& position, node*& address) const {
    int count = 0;
    address = head -> next;
    while (count < startPosition) {
        if (count + address -> size < startPosition) {
            count += address -> size;
            address = address -> next;
        }
        else {
            position = startPosition - count;
            return;
        }
    }
}

void linkedString::split(node* toSplit, int position) {
    toSplit -> next = new node(nodeSize, toSplit -> next);
    for (int i = position; i < toSplit -> size; i++)
        toSplit -> next -> data[i - position] = toSplit -> data[position];
    toSplit -> next -> size = toSplit -> size - position;
    toSplit -> size = position;
}

void linkedString::merge(node* toMerge) {
    node* toDelete = toMerge -> next;
    if (toMerge -> size + toDelete -> size <= nodeSize) {
        for (int position = 0; position < toDelete -> size; position++, toMerge -> size++)
            toMerge -> data[toMerge -> size] = toDelete -> data[position];
        toMerge -> next = toDelete -> next;
        delete toDelete;
    }
}

linkedString::linkedString(const char* source) {
    node* lastNode;
    for (stringLength = 0; source[stringLength] != '\0'; stringLength++);
    nodeSize = sqrt(stringLength);
    lastNode = head = new node(1);
    while (*source) {
        lastNode = lastNode -> next = new node(nodeSize);
        while (lastNode -> size < nodeSize && *source) {
            lastNode -> data[lastNode -> size] = *source;
            lastNode -> size++;
            source++;
        }
    }
}

linkedString::linkedString(const linkedString& source) {
    node* lastNode;
    node* sourceNode = source.head -> next;
    lastNode = head = new node(1);
    stringLength = source.stringLength;
    while (sourceNode) {
        lastNode = lastNode -> next = new node(nodeSize);
        while (lastNode -> size < sourceNode -> size) {
            lastNode -> data[lastNode -> size] = sourceNode -> data[lastNode -> size];
            lastNode -> size++;
        }
        sourceNode = sourceNode -> next;
    }
}

linkedString::~linkedString() {
    clear();
    delete head;
}

linkedString& linkedString::operator=(const linkedString& source) {
    if (this == &source)
        return *this;
    node* lastNode;
    node* sourceNode = source.head -> next;
    clear();
    stringLength = source.stringLength;
    while (sourceNode) {
        lastNode = lastNode -> next = new node(nodeSize);
        while (lastNode -> size < sourceNode -> size) {
            lastNode -> data[lastNode -> size] = sourceNode -> data[lastNode -> size];
            lastNode -> size++;
        }
        sourceNode = sourceNode -> next;
    }
    return *this;
}

linkedString linkedString::substr(int startPosition, int substringLength) const {
    linkedString substring;
    if (startPosition < 0 || startPosition >= stringLength - 1)
        return substring;
    int position;
    node* address;
    node* lastNode = substring.head;
    substringLength = (startPosition + substringLength > stringLength)? stringLength - startPosition : substringLength;
    substring.stringLength = substringLength;
    substring.nodeSize = sqrt(substringLength);
    findPosition(startPosition, position, address);
    for (int i = 0; i < substring.stringLength; ) {
        lastNode = lastNode -> next = new node(substring.stringLength);
        while (lastNode -> size < substring.nodeSize && i < substring.stringLength) {
            if (position == address -> size) {
                address = address -> next;
                position = 0;
            }
            lastNode -> data[lastNode -> size] = address -> data[position++];
            lastNode -> size++;
            i++;
        }
    }
    return substring;
}

int linkedString::length() const {
    return stringLength;
}

void linkedString::insert(int startPosition, const linkedString& source) {
    if (startPosition < 0 || startPosition > stringLength)
        return;
    node* address, * nextAddress, * lastNode;
    int position;
    findPosition(startPosition, position, address);
    split(address, position);
    nextAddress = address -> next;
    lastNode = source.head -> next;
    while (lastNode) {
        for (position = 0; position < lastNode -> size; position++) {
            if (address -> size == nodeSize)
                address = address -> next = new node(nodeSize);
            address -> data[address -> size] = address -> data[position];
            address -> size++;
        }
        lastNode = lastNode -> next;
    }
    stringLength += source.stringLength;
    address -> next = nextAddress;
    merge(address);
}

void linkedString::remove(int startPosition, int removeLength) {
    if (startPosition < 0 || startPosition >= stringLength - 1)
        return;
    node* startAddress;
    int position;
    findPosition(startPosition, position, startAddress);
    split(startAddress, position);
    if (startPosition + removeLength >= stringLength) {
        removeLength = stringLength - startPosition;
        stringLength = startPosition;
    }
    else
        stringLength -= removeLength;
    while (true) {
        node* nextAddress = startAddress -> next;
        if (removeLength > nextAddress -> size) {
            removeLength -= nextAddress -> size;
            startAddress -> next = nextAddress -> next;
            delete nextAddress;
        }
        else {
            split(nextAddress, removeLength);
            startAddress -> next = nextAddress -> next;
            delete nextAddress;
            break;
        }
    }
    merge(startAddress);
}

linkedString operator+(const linkedString& s1, const linkedString& s2) {
    char* result = new char[s1.stringLength + s2.stringLength + 1];
    int resultLength;
    for (linkedString::node* lastNode = s1.head -> next; lastNode != nullptr; lastNode = lastNode -> next)
        for (int i = 0; i < lastNode -> size; i++)
            result[resultLength++] = lastNode -> data[i];
    for (linkedString::node* lastNode = s2.head -> next; lastNode != nullptr; lastNode = lastNode -> next)
        for (int i = 0; i < lastNode -> size; i++)
            result[resultLength++] = lastNode -> data[i];
    result[resultLength] = '\0';
    linkedString sum(result);
    delete result;
    return sum;
}

bool operator>(const linkedString& s1, const linkedString& s2) {
    linkedString::node* ln1 = s1.head -> next, * ln2 = s2.head -> next;
    int position1 = 0, position2 = 0;
    while (ln1) {
        if (ln2 == nullptr)
            return true;
        if (ln1 -> data[position1] != ln2 -> data[position2])
            return ln1 -> data[position1] > ln2 -> data[position2] ? true : false;
        if (++position1 == ln1 -> size) {
            ln1 = ln1 -> next;
            position1 = 0;
        }
        if (++position2 == ln2 -> size) {
            ln2 = ln2 -> next;
            position2 = 0;
        }
    }
    return false;
}

bool operator<(const linkedString& s1, const linkedString& s2) {
    return !(s1 >= s2);
}

bool operator==(const linkedString& s1, const linkedString& s2) {
    if (s1.stringLength != s2.stringLength)
        return false;
    linkedString::node* ln1 = s1.head -> next, * ln2 = s2.head -> next;
    int position1 = 0, position2 = 0;
    while (ln1 && ln2) {
        if (ln1 -> data[position1] != ln2 -> data[position2])
            return false;
        if (++position1 == ln1 -> size) {
            ln1 = ln1 -> next;
            position1 = 0;
        }
        if (++position2 == ln2 -> size) {
            ln2 = ln2 -> next;
            position2 = 0;
        }
    }
    return true;
}

bool operator!=(const linkedString& s1, const linkedString& s2) {
    return !(s1 == s2);
}

bool operator>=(const linkedString& s1, const linkedString& s2) {
    return (s1 == s2 || s1 > s2);
}

bool operator<=(const linkedString& s1, const linkedString& s2) {
    return !(s1 > s2);
}

std::ostream& operator<<(std::ostream& os, const linkedString& s) {
    linkedString::node* lastNode = s.head -> next;
    while (lastNode) {
        for (int position = 0; position < lastNode -> size; position++)
            os << lastNode -> data[position];
        lastNode = lastNode -> next;
    }
    return os;
}
