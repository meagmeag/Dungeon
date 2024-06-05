//
// Created by meagh on 6/4/2024.
//

#ifndef DUNGEON_GAME_H
#define DUNGEON_GAME_H

#include "BasicFunctions.h"
#include "Creature.h"
using namespace std;


class Game : protected BasicFunctions {
public:
    Game();
    void Run();

private:
    void GetCorrectInput(string correctInput, string errorMessage);
    void NextDialogue(string action);
    void GetPlayerName();
    void Intro();
    void Combat(Creature monster);

    Creature player;
    Creature goblin; // temporary

    string input;
};


#endif //DUNGEON_GAME_H
