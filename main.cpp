//
// Created by meagh on 5/10/2024.
//
#include <iostream>
#include "Player.h"

using namespace std;

int main() {
    Creature goblin("goblin");
    goblin.AddItem(Backpack("huge sack", "mega huge", 100, 10));
    goblin.AddItem(Backpack());
    goblin.EquipItem("huge sack");
    goblin.AddItem(Item());
    goblin.AddItem(Item());
    goblin.AddItem(Item());
    goblin.AddItem(Item());
    goblin.EquipItem("unnamed backpack");
    goblin.EquipItem("huge sack");
    cout << goblin;
}