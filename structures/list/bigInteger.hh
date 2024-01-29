///
/// @file       bigInteger.hh
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       January 20, 2024
/// @version    0.3
/// @brief      The big integer class, trying to support large integer operations.
///

#if !defined(_LIBCPP_IOSTREAM) || !defined(_GLIBCXX_IOSTREAM)
    #include <iostream>
#endif
#if !defined(_LIBCPP_CSTRING) || !defined(_GLIBCXX_CSTRING)
    #include <cstring>
#endif

char* addition(const char*, const char*);
char* subtraction(const char*, const char*);
int numstrcmp(const char*, const char*);

class bigInteger {
    friend bigInteger operator+(const bigInteger&, const bigInteger&);
    friend bigInteger operator-(const bigInteger&, const bigInteger&);
    friend std::ostream& operator<<(std::ostream&, const bigInteger&);
    private:
        char sign;
        char* number;
    public:
        bigInteger(const char* original = "");
        bigInteger(const bigInteger&);
        ~bigInteger() {
            delete number;
        }
        bigInteger& operator=(const bigInteger&);
};

char* addition(const char* numberString1, const char* numberString2) {
    int length1 = strlen(numberString1);
    int length2 = strlen(numberString2);
    int minLength = length1 > length2 ? length2 : length1;
    int length = 1 + (length1 > length2 ? length1 : length2);
    int carry = 0; // 进位
    int digitSum;
    int i;
    char* numberString = new char[length + 1];
    for (i = 0; i < minLength; i++) {
        digitSum = numberString1[i] - '0' + numberString2[i] - '0' + carry;
        numberString[i] = digitSum % 10 + '0';
        carry = digitSum / 10;
    }
    while (i < length1) {
        digitSum = numberString1[i] - '0' + carry;
        numberString[i] = digitSum % 10 + '0';
        carry = digitSum / 10;
        i++;
    }
    while (i < length2) {
        digitSum = numberString2[i] - '0' + carry;
        numberString[i] = digitSum % 10 + '0';
        carry = digitSum / 10;
        i++;
    }
    if (carry != 0)
        numberString[i++] = carry + '0';
    numberString[i] = '\0';
    return numberString;
}

char* subtraction(const char* numberString1, const char* numberString2) {
    if (!strcmp(numberString1, numberString2))
        return "";
    int length1 = strlen(numberString1);
    int length2 = strlen(numberString2);
    int borrow = 0; // 借位
    int i;
    char* difference = new char[length1 + 1];
    for (i = 0; i < length2; i++) {
        difference[i] = numberString1[i] - numberString2[i] - borrow;
        if (difference[i] < 0) {
            difference[i] += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        difference[i] += '0';
    }
    while (i < length1) {
        difference[i] = numberString1[i] - '0' - borrow;
        if (difference[i] < 0) {
            difference[i] += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        i++;
    }
    do {
        i--;
    } while (i >= 0 && difference[i] == '0');
    difference[i + 1] = '\0';
    return difference;
}

int numstrcmp(const char* numberString1, const char* numberString2) {
    int length1 = strlen(numberString1);
    int length2 = strlen(numberString2);
    if (length1 != length2)
        return length1 - length2;
    for (int i = length1 - 1; i >= 0; i--) {
        if (numberString1[i] != numberString2[i])
            return numberString1[i] - numberString2[i];
    }
    return 0;
}

bigInteger::bigInteger(const char* original) {
    const char* absolute;
    switch (original[0]) {
        case '+':
            sign = '+';
            absolute = original + 1;
            break;
        case '-':
            sign = '-';
            absolute = original + 1;
            break;
        default:
            sign = '+';
            absolute = original;
            break;
    }
    if (strcmp(absolute, "0") == 0)
        absolute = "";
    int length = strlen(absolute);
    number = new char[length + 1];
    for (int i = 0; i < length; i++)
        number[length - i - 1] = absolute[i];
    number[length] = '\0';
}

bigInteger::bigInteger(const bigInteger& target) {
    sign = target.sign;
    number = new char[strlen(target.number + 1)];
    strcpy(number, target.number);
}

bigInteger& bigInteger::operator=(const bigInteger& rightValue) {
    if (this == &rightValue)
        return *this;
    delete number;
    sign = rightValue.sign;
    number = new char[strlen(rightValue.number + 1)];
    strcpy(number, rightValue.number);
    return *this;
}

std::ostream& operator<<(std::ostream& output, const bigInteger& toOutput) {
    if (strlen(toOutput.number) == 0)
        output << 0;
    else {
        output << toOutput.sign;
        for (int i = strlen(toOutput.number) - 1; i >=0; i--)
            output << toOutput.number[i];
    }
    return output;
}

bigInteger operator+(const bigInteger& bi1, const bigInteger& bi2) {
    bigInteger sum;
    delete sum.number;
    if (bi1.sign == bi2.sign) {
        sum.sign = bi1.sign;
        sum.number = addition(bi1.number, bi2.number);
    }
    else if (numstrcmp(bi1.number, bi2.number)) {
        sum.sign = bi1.sign;
        sum.number = subtraction(bi1.number, bi2.number);
    }
    else {
        sum.sign = bi2.sign;
        sum.number = subtraction(bi2.number, bi1.number);
    }
    return sum;
}

bigInteger operator-(const bigInteger& bi1, const bigInteger& bi2) {
    bigInteger opposite(bi2);
    if (opposite.sign == '+')
        opposite.sign = '-';
    else
        opposite.sign = '+';
    return bi1 + opposite;
}