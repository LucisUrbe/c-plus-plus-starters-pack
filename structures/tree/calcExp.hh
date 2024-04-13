///
/// @file       calcExp.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       April 14, 2024
/// @version    0.2
/// @brief      Calculate an expression with a string type and only int numbers, add/subtract/multiply/divide operations
///             and brackets, using a linked binary tree as the backend.
///

class calcExp {
private:
    enum Type {DAT, ADD, SUB, MUL, DIV, OPA, CPA, EOL};
    struct node {
        Type type;
        int data;
        node* leftNode, * rightNode;
        node(Type rawType, int rawData = 0, node* leftChild = nullptr, node* rightChild = nullptr): type(rawType), data(rawData), leftNode(leftChild), rightNode(rightChild) {}
    };
    node* rootNode;
    node* create(char*& expression);
    Type getToken(char*& expression, int& value);
    int result(node* root);
public:
    calcExp(char* expression) {
        rootNode = create(expression);
    }
    int result() {
        if (rootNode == nullptr)
            return 0;
        return result(rootNode);
    }
};

calcExp::node* calcExp::create(char*& expression) {
    calcExp::node* currentNode, * root = nullptr;
    Type returnType;
    int value;
    while (*expression) {
        returnType = calcExp::getToken(expression, value);
        switch (returnType) {
            case DAT:
            case OPA:
                if (returnType == DAT)
                    currentNode = new calcExp::node(DAT, value);
                else
                    currentNode = create(expression);
                if (root != nullptr)
                    if (root -> leftNode == nullptr)
                        root -> rightNode = currentNode;
                    else
                        root -> rightNode -> rightNode = currentNode;
                break;
            case CPA:
            case EOL:
                return root;
                break;
            case ADD:
            case SUB:
                if (root == nullptr)
                    root = new node(returnType, 0, currentNode);
                else
                    root = new node(returnType, 0, root);
                break;
            case MUL:
            case DIV:
                if (root == nullptr)
                    root = new node(returnType, 0, currentNode);
                else if (root -> type == MUL || root -> type == DIV)
                    root = new node(returnType, 0, root);
                else
                    root -> rightNode = new node(returnType, 0, root -> rightNode);
                break;
        }
    }
    return root;
}

calcExp::Type calcExp::getToken(char*& expression, int& value) {
    char type;
    while (*expression == ' ')
        expression++;
    if (*expression >= '0' && *expression <= '9') {
        value = 0;
        while (*expression >= '0' && *expression <= '9') {
            value = value * 10 + *expression - '0';
            expression++;
        }
        return DAT;
    }
    if (*expression == '\0')
        return EOL;
    type = *expression;
    expression++;
    switch (type) {
        case '+':
            return ADD;
            break;
        case '-':
            return SUB;
            break;
        case '*':
            return MUL;
            break;
        case '/':
            return DIV;
            break;
        case '(':
            return OPA;
            break;
        case ')':
            return CPA;
            break;
        default:
            return EOL;
            break;
    }
}

int calcExp::result(calcExp::node* toReturn) {
    int number_1, number_2;
    if (toReturn -> type == DAT)
        return toReturn -> data;
    number_1 = result(toReturn -> leftNode);
    number_2 = result(toReturn -> rightNode);
    switch (toReturn -> type) {
        case ADD:
            toReturn -> data = number_1 + number_2;
            break;
        case SUB:
            toReturn -> data = number_1 - number_2;
            break;
        case MUL:
            toReturn -> data = number_1 * number_2;
            break;
        case DIV:
            toReturn -> data = number_1 / number_2;
            break;
        default:
            break;
    }
    return toReturn -> data;
}
