//
// Created by meagh on 5/11/2024.
//

#ifndef DUNGEON_CONSUMABLE_H
#define DUNGEON_CONSUMABLE_H

#include "Item.h"

class Consumable : public Item {
public:
    Consumable();
    Consumable(string name, string description, int goldWorth, string useDescription, float dmgBuff, int numRounds);
    Consumable(string name, string description, int goldWorth, string useDescription, int hpRestore);
    friend ostream& operator<<(ostream& out, const Consumable& item);

    char GetType() const { return 'c'; }
    float GetDamageBuff() const { return dmgBuff; }
    int GetNumEffectRounds() const { return numRounds; }
    int GetHPRestored() const { return hpRestore; }
    string GetUseDescription() const { return useDescription; }

private:
    string useDescription;


    float dmgBuff;
    int numRounds;

    int hpRestore;
};


#endif //DUNGEON_CONSUMABLE_H
