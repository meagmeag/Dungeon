//
// Created by meagh on 6/4/2024.
//

#include "Game.h"

int main() {
    //Game game;
    //game.Run();
    Creature goblin("goblin", 1, 65);
    goblin.AddItem(Weapon("sword", "long", 20, 50));
    goblin.EquipItem("sword");
    cout << goblin;
    return 0;
}