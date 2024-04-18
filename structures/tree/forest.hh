///
/// @file       forest.hh
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2020
/// @date       April 18, 2024
/// @version    0.2
/// @brief      The forest class, storing multiple trees using a universal tree.
///


#include "universalTree.hh"

template<typename Type>
class singlyLinkedList {
private:
    struct node {
        Type data;
        node* next;
        node(const Type& rawData, node* nextNode = nullptr) {
            data = rawData;
            next = nextNode;
        }
        node() : next(nullptr) {}
        ~node() {}
    };
    int currentLength;
    node* head;
    node* where(int position) const {
        node* p = head;
        while (position-- > 0)
            p = p -> next;
        return p;
    }

public:
    singlyLinkedList() {
        head = new node(); // !!! !!! !!!
        currentLength = 0;
    }
    ~singlyLinkedList() {
        clear();
        delete head;
    }
    void insert(int position, const Type& rawData)  {
        node* toInsert = where(position);
        toInsert -> next = new node(rawData, toInsert -> next); // directly use of toInsert makes no change on the list
        currentLength++;
    }
    void clear()  {
        node* toDelete = head -> next, * nextDelete;
        head -> next = nullptr;
        while (toDelete != nullptr) {
            nextDelete = toDelete -> next;
            delete toDelete;
            toDelete = nextDelete;
        }
        currentLength = 0;
    }
    int length() const {
        return currentLength;
    }
    Type visit(int position) const {
        return where(position) -> data;
    }
};

template <typename Type>
class forest {
private:
    singlyLinkedList<universalTree<Type> > sll;
public:
    forest() {
        bool initial = false;
        while (true) {
            std::cout << "Start to plant " << sll.length() + 1 << " trees? ([y]/n): " << std::flush;
            std::cin.sync(); // macOS is not working well
            if (initial)
                std::getchar();
            char choice = std::getchar();
            switch (choice) {
                default:
                    continue;
                case '\n':
                case 'Y':
                case 'y':
                case 'N':
                case 'n':
                    break;
            }
            if (choice == 'n' || choice == 'N')
                break;
            universalTree<Type> ut;
            ut.create();
            sll.insert(sll.length(), ut);
            initial = true;
        }
    }
    ~forest() {
        sll.clear();
    }
    void find(Type toFind) const {
        bool found = false;
        for (int i = 0; i < sll.length(); i++)
            if (sll.visit(i + 1).find(toFind)) {
                std::cout << "The data is on the " << i + 1 << "(th) tree." << std::endl;
                found = true;
            }
        if (!found)
            std::cout << "The data " << toFind << " cannot be found in the forest." << std::endl;
    }
};
