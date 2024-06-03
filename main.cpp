//
// Created by meagh on 5/10/2024.
//
#include <iostream>
#include "Player.h"

using namespace std;

int main() {
    Creature goblin("goblin"); // test for first push!
    goblin.AddItem(Weapon());
    goblin.AddItem(Weapon("stick"));
    goblin.AddItem(Weapon("rock"));
    goblin.AddItem(Weapon("melon"));
    goblin.EquipWeapon("melon");
    goblin.RemoveItem("stick");
    goblin.AddItem(Weapon("sword", "sharp!", 10, 5.6));
    goblin.EquipWeapon("sword");
    goblin.UnequipWeapon("melon");
    goblin.RemoveItem("melon");
    cout << goblin.HasItem("melon");
    //cout << goblin;
}