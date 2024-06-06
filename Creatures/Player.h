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

   void LevelUp(int level);
};


#endif //DUNGEON_PLAYER_H
