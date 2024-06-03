//
// Created by meagh on 5/10/2024.
//
#include <iostream>
#include "Player.h"

using namespace std;

int main() {
    Creature goblin("goblin");
    goblin.AddItem(Weapon());
    goblin.EquipItem("pretty weak weapon");
    goblin.AddItem(Backpack());
    goblin.AddItem(Item());
    goblin.EquipItem("unnamed backpack");
    goblin.EquipItem("useless item");
    goblin.UnequipItem("pretty weak weapon");
    goblin.UnequipItem("unnamed backpack");
    cout << goblin;
}