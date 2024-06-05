//
// Created by meagh on 6/4/2024.
//

#ifndef DUNGEON_GAME_H
#define DUNGEON_GAME_H

#include "Creature.h"
using namespace std;


class Game {
public:
    Game();
    void Run();

private:
    void GetPlayerName();
    void Combat();

    Creature player;
    Creature goblin; // temporary
};


#endif //DUNGEON_GAME_H
