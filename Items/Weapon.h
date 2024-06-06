//
// Created by meagh on 5/10/2024.
//

#ifndef DUNGEON_CRAWLER_WEAPON_H
#define DUNGEON_CRAWLER_WEAPON_H

#include "Item.h"
using namespace std;

class Weapon : public Item {
public:
    Weapon();
    Weapon(string name);
    Weapon(string name, string description);
    Weapon(string name, string description, int goldWorth, float dmgBuff);
    friend ostream& operator<<(ostream& out, const Weapon& item);

    char GetType() const { return 'w'; }
    float GetDamageBuff()  const { return dmgBuff; }

private:
    float dmgBuff;
    void StandardizeDamageBuff();
};


#endif //DUNGEON_CRAWLER_WEAPON_H
