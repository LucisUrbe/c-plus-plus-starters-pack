///
/// @file       19-cell-growth.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 9, 2024
/// @version    0.2
/// @brief      The use of class constructors, destructors and members.
/// @note       Do not moidify or write more code unless allowed in
///             the limited places (see comments).
///

#include <iostream>
using namespace std;

class Cell {
    // Write some code below.
    // Step 1: declare essential member variables
private:
    int size;
    static int resource;
    // Step 2: declare constructors, destructor and member operations
public:
    Cell(int);
    Cell(const Cell&);
    ~Cell();
    static int get_resource();
    int get_size();
    void grow() const;
    void grow(int);
    void eat(int, Cell*&) const;
    // Write some code above.
};

int main() {
    int init_size, id = 1, eaten = 0, i, size, eat;
    Cell *cells[100] = {0};
    cout << "Initial Cell Size: ";
    cin >> init_size;
    const Cell *init_cell = new const Cell(init_size);
    cout << "Initial Cell is born, remaining resource = " << Cell::get_resource() << endl;

    cells[0] = new Cell(*init_cell);
    cout << "Cell 0 is born, remaining resource = " << Cell::get_resource() << endl;
    while (true) {
        // Write some code below.
        // Step 3: guess the code to be written from the output demonstration
        // First, grow the "init_cell".
        init_cell -> grow();
        // Then, let other cells grow if the conditions meet.
        for (int i = 0, stop = id; i < stop && Cell::get_resource() > 0 && id <= 100; i++)
            if (cells[i]) {
                cells[i] -> grow(i);
                // Spawn more normal cells if the resources are enough.
                if (cells[i] -> get_size() > 5 && Cell::get_resource() >= cells[i] -> get_size() / 2) {
                    cells[id] = new Cell(cells[i] -> get_size() / 2);
                    cout << "Cell " << id++ << " is born, remaining resource = " << Cell::get_resource() << endl;
                }
            }
        // Choose one with the biggest size from normal cells.
        for (i = 0, size = 0; i < id; i++) 
            if (cells[i])
                if (cells[i] -> get_size() > size) {
                    size = cells[i] -> get_size();
                    eat = i;
                }
        // init_cell would eat cells if the conditions meet.
        if (size > 10 && Cell::get_resource() > 0)
            init_cell -> eat(eat, cells[eat]);
        // Finally, recycle all memory space and break the loop if the conditions meet.
        if (Cell::get_resource() <= 0 || id > 100) {
            delete init_cell;
            for (int i = 0; i < id && cells[i]; i++)
                delete cells[i];
            break;
        }
        // Write some code above.
    }

    return 0;
}

// Write some code below.（"Cell" class definitions）
// Step 4: initialize static class objects
int Cell::resource = 500;

// Step 5: define all the functions of the class

/// @brief Get the private member "resource" of the class.
int Cell::get_resource() {
    return resource;
}

/// @brief Get the private member "resource" of the class (normal cells only).
int Cell::get_size() {
    return size;
}

/// @brief Constructor of new normal cells.
Cell::Cell(int spawnSize) {
    if (spawnSize < 1 || spawnSize > 100) {
        cout << "Cell initialization failed." << endl;
        return;
    }
    size = spawnSize;
    resource -= spawnSize;
}

/// @brief Constructor of the initial cell (Cell #0).
Cell::Cell(const Cell& initialCell) {
    size = initialCell.size / 2;
    resource -= initialCell.size / 2;
}

/// @brief Let the initial cell grow.
void Cell::grow() const {
    resource--;
    cout << "Initial Cell grows, remaining resource = " << resource << endl;
}

/// @brief Let normal cells grow.
void Cell::grow(int id) {
    size++;
    resource--;
    cout << "Cell " << id << " grows, remaining resource = " << resource << endl;
}

/// @brief Let the initial cell eat.
void Cell::eat(int id, Cell*& CellToEat) const {
    delete CellToEat;
    CellToEat = nullptr;
    cout << "Cell " << id << " is eaten, remaining resource = " << resource << endl;
}

/// @brief Let resources more if a cell dies.
Cell::~Cell() {
    resource += size;
}
