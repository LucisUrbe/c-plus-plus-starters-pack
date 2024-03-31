///
/// @file       15-games-class-members.cc
/// @author     Lucis Urbe
/// @copyright  Shanghai Jiao Tong University, 2019
/// @date       January 8, 2024
/// @version    0.2
/// @brief      The use of class.
///

#include <iostream>
#define HEAL_VALID 20
#define HEAL_EFFECT 10
using namespace std;

struct Actor {
    // Define something below.
    char* name;
    int hp, atk, def;
    bool heal;
};

Actor &GetPlayer(char[], int);
Actor &GetEnemy(int);
void Action(Actor&, Actor&, int);

int main() {
    char name[10];
    int money, act;
    cout << "What's your name? (No more than 9 letters) ";
    cin >> name;
    cout << "How much will you pay for the game? $";
    cin >> money;
    Actor &player = GetPlayer(name, money);
    Actor &enemy = GetEnemy(money);
    cout << "===== " << player.name << " vs " << enemy.name << " =====" << endl;
    if (money < 1) {
        cout << "You Lose!" << endl;
        return 0;
    }
    for (int i = 1; i <= 10; ++i) {
        cout << "Round " << i << endl;
        // Write some code below.
        cout << player.name << (player.heal ? "'s act (1-attack; 2-heal; otherwise-wait): " : "'s act (1-attack; otherwise-wait): ");
        cin >> act;
        if (!player.heal && act == 2)
            act++;
        Action(player, enemy, act);
        if (enemy.hp < 10 && enemy.heal)
            act = 2;
        else
            act = 1;
        Action(enemy, player, act);
        if (player.hp > 0 && enemy.hp <= 0) {
            cout << "You Win!" << endl;
            return 0;
        }
        else if (enemy.hp > 0 && player.hp <= 0) {
            cout << "You Looose!" << endl;
            return 0;
        }
        else if (player.hp <= 0 && enemy.hp <= 0) {
            cout << "End of Game with Draw." << endl;
            return 0;
        }
        cout << player.name << "'s remaining HP: " << player.hp << endl;
        cout << enemy.name << "'s remaining HP: " << enemy.hp << endl;
        cout << "------------------------------------------" << endl;
    }
    cout << "End of Game with Draw." << endl; // draw: v. & n. 平局
    return 0;
}

Actor &GetPlayer(char name[], int m) {
    Actor *player = new Actor({name, m, m / 2, m / 3, m >= HEAL_VALID});
    // Write some code below.
    cout << "Welcome to this game, " << player -> name << "!\n";
    cout << "Your status: HP" << player -> hp << ", ATK" << player -> atk << ", DEF" << player -> def << '\n';
    cout <<  (player -> heal ? "You can attack the enemy and heal yourself." : "You can attack the enemy but not heal yourself.") << endl;
    return *player;
}

Actor &GetEnemy(int m) {
    Actor *enemy;
    int choice;
    cout << "Input a digit to choose your enemy (0 for Wolf, or otherwise Slime): ";
    cin >> choice;
    if (choice)
        enemy = new Actor({(char*)"Slime", 20 + m / 5, 8 + m / 6, 7 + m / 6, true});
    else
        enemy = new Actor({(char*)"Wolf", 25 + m / 4, 9 + m / 6, 6 + m / 6, false});
    // Write some code below.
    cout << "Your enemy " << enemy -> name << ": HP" << enemy -> hp << ", ATK" << enemy -> atk << ", DEF" << enemy -> def << endl;
    return *enemy;
}

void Action(Actor &user, Actor &target, int act) {
    if (act == 1) {
        cout << user.name << " attacks " << target.name << "!" << endl;
        int damage = user.atk - target.def;
        if (damage < 0)
            damage = 0;
        target.hp -= damage;
    }
    else if (act == 2) {
        cout << user.name << " does self-healing!" << endl;
        user.hp += HEAL_EFFECT;
    }
    else
        cout << user.name << " is waiting..." << endl;
}
