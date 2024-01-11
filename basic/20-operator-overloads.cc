///
/// @file       20-operator-overloads.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 11, 2024
/// @version    0.2
/// @brief      The use of class operators.
/// @note       Do not moidify or write more code unless allowed in
///             the limited places (see comments).
///


#include <iostream>
using namespace std;

class Cell {
    friend istream &operator>>(istream &, Cell &);
    protected:
        int size;
        static int resource;
    public:
        int get_size() const {
            return size;
        }
        bool grow();
};


class NewCell: public Cell {
    friend ostream& operator<<(ostream& output, NewCell& target);
    private:
        int id;
        static int counter;
    public:
        bool operator=(Cell& source);
        bool operator=(NewCell& source);
        bool grow(void);
};

int main() {
    Cell init_cell;
    NewCell cells[100];
    int born = 1, eaten = 0, maxsize;

    cout << "Initial Cell Size: ";
    cin >> init_cell;
    if (cells[0] = init_cell)
        return 0;

    while (true) {
        if (init_cell.grow())
            return 0;
        int thisround = born;
        for (int i = 0; i < thisround; ++i) {
            if (cells[i].get_size() == 0)
                continue;
            if (cells[i].grow())
                return 0;
            if (cells[i].get_size() > 5) {
                if (cells[born] = cells[i])
                    return 0;
                if (cells[born].get_size() > cells[eaten].get_size())
                    eaten = born;
                born++;
                if (born >= 100)
                    return 0;
            }
        }
        if (cells[eaten].get_size() > 10) {
            cout << cells[eaten];
            eaten = 0, maxsize = 0;
            for (int i = 0; i < born; ++i)
                if (cells[i].get_size() > maxsize) {
                    maxsize = cells[i].get_size();
                    eaten = i;
                }
        }
    }
    return 0;
}

int Cell::resource = 500;
int NewCell::counter = 0;


istream &operator>>(istream& input, Cell& initialCell) {
    int spawnSize;
    input >> spawnSize;
    if (spawnSize < 1 || spawnSize > 100) {
        cerr << "*** Invalid input! The input is now changed to 1. ***" << endl;
        spawnSize = 1;
    }
    initialCell.size = spawnSize;
    Cell::resource -= spawnSize;
    cout << "Initial Cell is born, remaining resource = " << Cell::resource << endl;
    return input;
}

ostream& operator<<(ostream& output, NewCell& target) {
    NewCell::resource += target.size;
    target.size -= target.size;
    output << "Cell " << target.id << " is eaten, remaining resource = " << NewCell::resource << endl;
    return output;
}

bool NewCell::operator=(Cell& initialCell) {
    if (this == &initialCell)
        return true;
    this -> id = counter++;
    this -> size = initialCell.get_size() / 2;
    resource -= initialCell.get_size() / 2;
    cout << "Cell " << id << " is born, remaining resource = " << Cell::resource << endl;
    return false;
}

bool NewCell::operator=(NewCell& source) {
    if (this == &source)
        return true;
    if (resource < source.size / 2)
        return false;
    this -> id = counter++;
    this -> size = source.size / 2;
    resource -= source.size / 2;
    cout << "Cell " << id << " is born, remaining resource = " << Cell::resource << endl;
    return false;
}

bool Cell::grow(void) {
    if (resource <= 0)
        return true;
    resource--;
    cout << "Initial Cell grows, remaining resource = " << resource << endl;
    return false;
}

bool NewCell::grow(void) {
    if (resource <= 0)
        return true;
    this -> size++;
    resource--;
    cout << "Cell " << id << " grows, remaining resource = " << resource << endl;
    return false;
}
//