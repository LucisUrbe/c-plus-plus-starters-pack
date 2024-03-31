///
/// @file       parenthesis_matching.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       January 31, 2024
/// @version    0.2
/// @brief      The header file of parenthesis matching program.
///

#if !defined(_LIBCPP_IOSTREAM) || !defined(_GLIBCXX_IOSTREAM)
    #include <iostream>
#endif
#if !defined(_LIBCPP_FSTREAM) || !defined(_GLIBCXX_FSTREAM)
    #include <fstream>
#endif
#include "sequenceStack.hh"

class matching {
    private:
        std::ifstream fin;
        int currentLine;
        int errors;
        struct symbol {
            char token;
            int line;
        };
        enum comment {
            slash_slash,
            slash_star
        };
        bool checkMatching(char symbol1, char symbol2, int line1, int line2);
        char getNextSymbol();
        void putBackChar(char toPut);
        void skipComment(enum comment type);
        void skipQuote(char type);
        char nextChar();
    public:
        matching(const char* fileName);
        int checkIfMatching();
};

class noFileException {};

matching::matching(const char* fileName) {
    fin.open(fileName);
    if (!fin)
        throw noFileException();
    currentLine = 1;
    errors = 0;
}

int matching::checkIfMatching() {
    struct symbol node;
    sequenceStack<symbol> ss;
    char lastChar, toMatch;
    while ((lastChar = getNextSymbol())) {
        switch (lastChar) {
            case '(':
            case '[':
            case '{':
                node.token = lastChar;
                node.line = currentLine;
                ss.push(node);
                break;
            case ')':
            case ']':
            case '}':
                if (ss.isEmpty()) {
                    errors++;
                    std::cout << "Line " << currentLine << " has an unmatched " << lastChar << std::endl;
                }
                else {
                    node = ss.pop();
                    toMatch = node.token;
                    if (!checkMatching(toMatch, lastChar, node.line, currentLine))
                        errors++;
                }
                break;
        }
    }
    while (!ss.isEmpty()) {
        errors++;
        node = ss.pop();
        std::cout << "Line " << node.line << "has a " << node.token << " that is unmatched" << std::endl;
    }
    return errors;
}

bool matching::checkMatching(char symbol1, char symbol2, int line1, int line2) {
    if ((symbol1 == '(' && symbol2 == ')') || (symbol1 == '[' && symbol2 == ']') || (symbol1 == '{' && symbol2 == '}'))
        return true;
    else {
        std::cout << "Line " << line2 << " has a " << symbol2 << " and line " << line1 << " has " << symbol1 << " but the two are unmatched" << std::endl;
        return false;
    }
}

char matching::getNextSymbol() {
    char next;
    while ((next = nextChar())) {
        if (next == '/') {
            next = nextChar();
            if (next == '*')
                skipComment(slash_star);
            else if (next == '/')
                skipComment(slash_slash);
            else
                putBackChar(next);
        }
        else if (next == '\'' || next == '\"')
            skipQuote(next);
        else if (next == '(' || next == ')' || next == '[' || next == ']' || next == '{' || next == '}')
            return next;
    }
    return '\0';
}

void matching::putBackChar(char toPut) {
    fin.putback(toPut);
    if (toPut == '\n')
        currentLine--;
    return;
}

void matching::skipComment(enum comment type) {
    char next, previousNext = ' ';
    if (type == slash_slash) {
        while ((next = nextChar()) && (next != '\n'));
        return;
    }
    while ((next = nextChar()) != '\0') {
        if (previousNext == '*' && next == '/')
            return;
        previousNext = next;
    }
    errors++;
    std::cout << "Comment is not fully wrapped!" << std::endl;
    return;
}

void matching::skipQuote(char type) {
    char next;
    while ((next = nextChar())) {
        if (next == type)
            return;
        else if (next == '\n') {
            errors++;
            std::cout << "Line " << currentLine << " has a missing quotation mark" << std::endl;
            return;
        }
        else if (next == '\\')
            next = nextChar();
    }
    return;
}

char matching::nextChar() {
    char next;
    if ((next = fin.get()) == EOF)
        return '\0';
    if (next == '\n')
        currentLine++;
    return next;
}
