///
/// @file       18-game-class-constructor.cc
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 9, 2024
/// @version    0.2
/// @brief      The use of class.
/// @note       Do not moidify or write more code unless allowed in
///             the limited places (see comments).
///

#include <iostream>

#define HEAL_VALID 20
#define HEAL_EFFECT 10
#define TOTAL_MONEY 50

using namespace std;

class Weapon {
    // Write some code below.
    public:
    Weapon(int a, int b): effect(a), price(b) {}
    // Write some code above.
    const int effect;
    const int price;
};

class Actor {
    char *name;
    int hp;
    int atk;
    int def;
    bool heal;
    bool isPlayer;
    // Write some code below.
    public:
    Actor(char[], int);
    Actor(int, int);
    void Action(Actor &);
    // Write some code above.
    void equip(Weapon &w) {
        atk += w.effect;
    };
    char *get_name() {
        return name;
    };
    int get_hp() {
        return hp;
    };
};

int main() {
    char name[10];
    int money, enemy_choice, weapon_choice;
    Weapon sword(10, 10);
    cout << "What's your name? (No more than 9 letters) ";
    cin >> name;
    cout << "You have $" << TOTAL_MONEY << " in total." << endl;
    cout << "How much will you pay for your basic attributes? $";
    cin >> money;
    Actor player(name, money);
    cout << "---------------------" << endl;
    cout << "Input a digit to choose your enemy (0 for Wolf, or otherwise Slime): ";
    cin >> enemy_choice;
    Actor enemy(enemy_choice, money);
    cout << "---------------------" << endl;
    cout << "You have $" << TOTAL_MONEY - money << " left." << endl;
    if (TOTAL_MONEY - money >= sword.price) {
        cout << "If you want to spend $10 to buy a sword, input 1: ";
        cin >> weapon_choice;
        if (weapon_choice == 1) {
            cout << name << " has a sword now! ATK+" << sword.effect << "!" << endl;
            player.equip(sword);
        } else
            cout << name << " has no sword." << endl;
    }
    cout << "===== " << player.get_name() << " vs " << enemy.get_name() << " =====" << endl;
    if (money < 1) {
        cout << "You Looose!" << endl;
        return 0;
    }
    for (int i = 1; i <= 10; ++i) {
        cout << "Round " << i << endl;
        player.Action(enemy);
        enemy.Action(player);
        cout << player.get_name() << "'s remaining HP: " << player.get_hp() << endl;
        cout << enemy.get_name() << "'s remaining HP: " << enemy.get_hp() << endl;
        cout << "---------------------" << endl;
        // Write some code below so that the output is the same as in the file "15-game-class-members.cc"
        if (player.get_hp() > 0 && enemy.get_hp() <= 0) {
            cout << "You Win!" << endl;
            return 0;
        }
        else if (enemy.get_hp() > 0 && player.get_hp() <= 0) {
            cout << "You Looose!" << endl;
            return 0;
        }
        else if (player.get_hp() <= 0 && enemy.get_hp() <= 0) {
            cout << "End of Game with Draw." << endl;
            return 0;
        }
    }
    cout << "End of Game with Draw." << endl;
    return 0;
}

// Write some code below so that the input/output is the same as in the file "15-game-class-members.cc"
Actor::Actor(char a[], int b): name(a), hp(b), atk(b / 2), def(b / 3), heal(b >= HEAL_VALID), isPlayer(true) {
    cout << "Welcome to this game, " << name << "!\n";
    cout << "Your status: HP" << hp << ", ATK" << atk << ", DEF" << def << '\n';
    cout << "You can attack the enemy " << (heal ? "and" : "but not") << " heal yourself." << endl;
    cout << "You can act with 1 to attack the enemy, " << (heal ? "2 to heal yourself, " : "") << "and otherwise wait." << endl;
}
// Define a function below so that the attributes behave the same as in the file "15-game-class-members.cc"
Actor::Actor(int a, int b): heal(a), isPlayer(false) {
    if (heal) {
        name = (char*)"Slime";
        hp = 20 + b / 5;
        atk = 8 + b / 6;
        def = 7 + b / 6;
        }
    else {
        name = (char*)"Wolf";
        hp = 25 + b / 4;
        atk = 9 + b / 6;
        def = 6 + b / 6;
    }
    cout << "Your enemy " << name << ": HP" << hp << ", ATK" << atk << ", DEF" << def << endl;
}
// Define a function below so that the attributes behave the same as in the file "15-game-class-members.cc"
void Actor::Action(Actor &entity) {
    int act;
    if (!entity.isPlayer) {
        cout << this -> name << "'s act (1-attack; " << (this -> heal ? "2-heal; " : "") << "otherwise-wait): " << flush;
        cin >> act;
        if (!(this -> heal) && act == 2)
            act++;
    }
    else {
        if (this -> hp < 10 && this -> heal)
            act = 2;
        else
            act = 1;
    }
    if (act == 1) {
        cout << this -> name << " attacks " << entity.name << "!" << endl;
        int damage = this -> atk - entity.def;
        if (damage < 0)
            damage = 0;
        entity.hp -= damage;
    }
    else if (act == 2) {
        cout << this -> name << " does self-healing!" << endl;
        this -> hp += HEAL_EFFECT;
    }
    else
        cout << this -> name << " is waiting..." << endl;
}
