///
/// @file       sequenceString.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       March 18, 2024
/// @version    0.2
/// @brief      The sequence string class, storing a string in a char sequence.
///

#if !defined(_LIBCPP_IOSTREAM) || !defined(_GLIBCXX_IOSTREAM)
    #include <iostream>
#endif

class sequenceString {
    private:
        friend sequenceString operator+(const sequenceString& s1, const sequenceString& s2);
        friend bool operator<(const sequenceString& s1, const sequenceString& s2);
        friend bool operator>(const sequenceString& s1, const sequenceString& s2);
        friend bool operator==(const sequenceString& s1, const sequenceString& s2);
        friend bool operator!=(const sequenceString& s1, const sequenceString& s2);
        friend bool operator<=(const sequenceString& s1, const sequenceString& s2);
        friend bool operator>=(const sequenceString& s1, const sequenceString& s2);
        friend std::ostream& operator<<(std::ostream& os, const sequenceString& s);
        char* data = nullptr; // Initial value should be robust.
        int stringLength;
    public:
        sequenceString(const char* source = "");
        sequenceString(const sequenceString& source);
        ~sequenceString();
        sequenceString& operator=(const sequenceString& source);
        sequenceString substr(int startPosition, int substringLength) const;
        int length() const;
        void insert(int startPosition, const sequenceString& source);
        void remove(int startPosition, int removeLength);
};

sequenceString::sequenceString(const char* source) {
    for (stringLength = 0; source[stringLength] != '\0'; stringLength++);
    data = new char[stringLength + 1];
    for (stringLength = 0; source[stringLength] != '\0'; stringLength++)
        data[stringLength] = source[stringLength];
    data[stringLength] = '\0';
}

sequenceString::sequenceString(const sequenceString& source) {
    data = new char[source.stringLength + 1];
    for (stringLength = 0; stringLength <= source.stringLength; stringLength++)
        data[stringLength] = source.data[stringLength];
}

sequenceString::~sequenceString() {
    delete data;
}

sequenceString& sequenceString::operator=(const sequenceString& source) {
    if (this == &source)
        return *this;
    delete data;
    data = new char[source.stringLength + 1];
    for (stringLength = 0; stringLength <= source.stringLength; stringLength++)
        data[stringLength] = source.data[stringLength];
    return *this;
}

sequenceString sequenceString::substr(int startPosition, int substringLength) const {
    if (startPosition >= stringLength - 1 || startPosition < 0 || data == nullptr)
        return "";
    sequenceString substring;
    substring.stringLength = (startPosition + substringLength > stringLength) ? stringLength - startPosition : substringLength;
    delete substring.data;
    substring.data = new char[substring.stringLength + 1];
    for (int i = 0; i < substring.stringLength; i++)
        substring.data[i] = data[startPosition + i];
    substring.data[substring.stringLength] = '\0';
    return substring;
}

int sequenceString::length() const {
    return stringLength;
}

void sequenceString::insert(int startPosition, const sequenceString& source) {
    char* origin = data;
    if (startPosition > stringLength || startPosition < 0 || data == nullptr)
        return;
    stringLength += source.stringLength;
    data = new char[stringLength + 1];
    int i;
    for (i = 0; i < startPosition; i++)
        data[i] = origin[i];
    for (i = 0; i < source.stringLength; i++)
        data[startPosition + i] = source.data[i];
    for (i = startPosition; origin[i] != '\0'; i++)
        data[source.stringLength + i] = origin[i];
    data[source.stringLength + i] = '\0';
    delete origin;
}

void sequenceString::remove(int startPosition, int removeLength) {
    if (startPosition >= stringLength - 1 || startPosition < 0 || data == nullptr)
        return;
    if (startPosition + removeLength >= stringLength) {
        data[startPosition] = '\0';
        stringLength = startPosition;
        return;
    }
    else {
        for (stringLength = startPosition; data[stringLength + removeLength] != '\0'; stringLength++)
            data[stringLength] = data[stringLength + removeLength];
        data[stringLength] = '\0';
        return;
    }
    return;
}

sequenceString operator+(const sequenceString& s1, const sequenceString& s2) {
    sequenceString sum;
    sum.stringLength = s1.stringLength + s2.stringLength;
    delete sum.data;
    sum.data = new char[sum.stringLength + 1];
    for (int i = 0; i < s1.stringLength; i++)
        sum.data[i] = s1.data[i];
    for (int i = 0; i < s2.stringLength; i++)
        sum.data[i + s1.stringLength] = s2.data[i];
    return sum;
}

bool operator<(const sequenceString& s1, const sequenceString& s2) {
    return !(s1 >= s2);
}

bool operator>(const sequenceString& s1, const sequenceString& s2) {
    for (int i = 0; i < s1.stringLength; i++)
        if (s1.data[i] != s2.data[i])
            return s1.data[i] > s2.data[i] ? true : false;
    return false;
}

bool operator==(const sequenceString& s1, const sequenceString& s2) {
    if (s1.stringLength != s2.stringLength)
        return false;
    for (int i = 0; i < s1.stringLength; i++)
        if (s1.data[i] != s2.data[i])
            return false;
    return true;
}

bool operator!=(const sequenceString& s1, const sequenceString& s2) {
    return !(s1 == s2);
}

bool operator<=(const sequenceString& s1, const sequenceString& s2) {
    return !(s1 > s2);
}

bool operator>=(const sequenceString& s1, const sequenceString& s2) {
    return (s1 > s2 || s1 == s2);
}

std::ostream& operator<<(std::ostream& os, const sequenceString& s) {
    os << s.data;
    return os;
}
