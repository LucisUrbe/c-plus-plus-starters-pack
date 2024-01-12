///
/// @file       20-operator-overloads.cc
/// @author     Gilbert Jin
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 12, 2024
/// @version    0.2
/// @brief      The use of fstream objects.
/// @note       Do not moidify or write more code unless allowed in
///             the limited places (see comments).
///

#include <iostream>
#include <fstream>
#define NUM 20
using namespace std;

class Team;
template <class T> class Actor;
// Declare a function template below.
template <class T> ifstream &operator>>(ifstream&, Actor<T>&);
// Declare a function template above.

template <class T>
class Actor {
    // Declare a friend which is a overload function template of the input operator of class "Actor".
    template <class Type>
    friend ifstream &operator>>(ifstream&, Actor<Type>&);
    //
    // Declare a friend which is a overload function of the input operator of class "Team".
    friend ofstream &operator<<(ofstream&, Team&);
    //
private:
    int id;
    char name[10];
    T hp;
    T atk;
    T def;
public:
    bool heal;
    Actor(int i = 0, bool h = false): id(i), heal(false) {} // heal(h)?
};

class Team {
    // Declare a friend, three private data members and define a public constructor.
    friend ofstream &operator<<(ofstream&, Team&);
private:
    Actor<int> finalIntActor[NUM];
    Actor<float> finalFloatActor[NUM];
    int finalThreshold;
public:
    Team(Actor<int>* intActor, Actor<float>* floatActor, int threshold) {
        for (int i = 0; i < NUM; i++) {
            finalIntActor[i] = intActor[i];
            finalFloatActor[i] = floatActor[i];
        }
        finalThreshold = threshold;
    }
    //
};

int main() {
    // Declare two arrays below.
    Actor<int> intActor[NUM];
    Actor<float> floatActor[NUM];
    // Declare two arrays above.
    char waste[100], test;
    int threshold, i;
    // Write some code below to read files. Do not define new objects unless file stream objects.
    ifstream finInt("actors_int.txt"), finFloat("actors_float.txt");
    if (!finInt) {
        cout << "***Invalid input file \"actors_int.txt\". The program now exits.***" << endl;
        return -1;
    }
    if (!finFloat) {
        cout << "***Invalid input file \"actors_float.txt\". The program now exits.***" << endl;
        return -2;
    }
    finInt >> waste >> waste >> waste >> waste >> waste;
    for (i = 0; !finInt.eof() && i < NUM; i++) {
        finInt >> intActor[i];
        finInt.get(test);
        if (test == '\t') {
            intActor[i].heal = true;
            finInt >> waste;
        }
    }
    finFloat >> waste >> waste >> waste >> waste >> waste;
    for (i = 0; !finFloat.eof() && i < NUM; i++) {
        finFloat >> floatActor[i];
        finFloat.get(test);
        if (test == '\t') {
            floatActor[i].heal = true;
            finFloat >> waste;
        }
    }
    //
    cout << "Standard (%): ";
    cin >> threshold;
    Team team(intActor, floatActor, threshold);
    ofstream fout("team.txt");
    fout << team;
    fout.close();
    return 0;
}

// Define the overload function template of the input operator of class "Actor".
template <class T>
ifstream &operator>>(ifstream& input, Actor<T>& target) {
    input >> target.id >> target.name >> target.hp >> target.atk >> target.def;
    return input;
}
//

// Define the overload function of the input operator of class "Team".
ofstream &operator<<(ofstream& output, Team& target) {
    output << "ID\tName\tHP\tATK\tDEF\n";
    int i, j, flag;
    for (i = j = flag = 0; i < NUM && target.finalIntActor[i].id == i + 1; i++) {
        if (target.finalIntActor[i].hp > target.finalThreshold)
            flag++;
        if (target.finalIntActor[i].atk > target.finalThreshold / 3)
            flag++;
        if (target.finalIntActor[i].def > target.finalThreshold / 3)
            flag++;
        if (target.finalIntActor[i].heal)
            flag++;
        if (flag >= 3) {
            j++;
            output << i << '\t' << target.finalIntActor[i].name << '\t' << target.finalIntActor[i].hp << '\t' << target.finalIntActor[i].atk << '\t' << target.finalIntActor[i].def;
            if (target.finalIntActor[i].heal)
                output << "\thealer";
            output << '\n';
        }
        flag = 0;
    }
    for (i = flag = 0; i < NUM && target.finalFloatActor[i].id == i + 1; i++) {
        if (target.finalFloatActor[i].hp > target.finalThreshold)
            flag++;
        if (target.finalFloatActor[i].atk > target.finalThreshold / 3)
            flag++;
        if (target.finalFloatActor[i].def > target.finalThreshold / 3)
            flag++;
        if (target.finalFloatActor[i].heal)
            flag++;
        if (flag >= 3) {
            output << ++j << '\t' << target.finalFloatActor[i].name << '\t' << target.finalFloatActor[i].hp << '\t' << target.finalFloatActor[i].atk << '\t' << target.finalFloatActor[i].def;
            if (target.finalFloatActor[i].heal)
                output << "\thealer";
            output << '\n';
        }
        flag = 0;
    }
    return output;
}
//
