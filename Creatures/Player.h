//
// Created by meagh on 5/11/2024.
//

#ifndef DUNGEON_PLAYER_H
#define DUNGEON_PLAYER_H

#include "Creature.h"

class Player : public Creature {
public:
   Player();
   Player(string name);
   friend ostream& operator<<(ostream& out, const Player& player);

   int LevelUp();
   int GainXP(int XP);
   string PrintXP() const;
   int neededXP; // make private!!!

private:
    int currXP;
    const float PLAYER_HEALTH_PERCENT = .9;
};


#endif //DUNGEON_PLAYER_H
