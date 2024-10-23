//
// Created by meagh on 6/4/2024.
//

#ifndef DUNGEON_GAME_H
#define DUNGEON_GAME_H

#include "GameObject.h"
#include "Player.h"
using namespace std;


class Game : protected GameObject {
public:
    Game();
    void Run();

private:
    //printing
    void PrintBreak() const;
    void PrintPlayer();
    void PrintPlayerHealth();
    void PrintPlayerInventory();

    void GetCorrectInput(string correctInput, string errorMessage);
    void NextDialogue(const string& action = "to continue");
    void GetPlayerName();
    void Intro();
    void SimpleCombat(Creature monster);

    Player player;
    string input;
};


#endif //DUNGEON_GAME_H
