//
// Created by meagh on 5/10/2024.
//

#ifndef DUNGEON_CRAWLER_CREATURE_H
#define DUNGEON_CRAWLER_CREATURE_H

#include "BasicFunctions.h"
#include "Inventory.h"
using namespace std;

/**
 * CREATURE RULES:
 *
 * "Resources" are 15 X level X 1.1^level.
 * Health cannot be more than 90% of resources or less than 75%.
 * Health + Base Damage must equal resources
 **/

class Creature : protected BasicFunctions {
public:
    Creature();
    Creature(string name);
    Creature(string name, float healthPercent);
    Creature(string name, float healthPercent, int level);

    // printing
    friend ostream& operator<<(ostream &out, const Creature& creature);
    string PrintLevel() const;
    string PrintHealth() const;
    string PrintBaseDamage() const;
    string PrintTotalDamage() const;
    string PrintInventory() const;
    string PrintXPWorth() const;

    // get info
    string GetName() const { return name; }
    void SetName(string name);
    int GetMaxHealth() const { return maxHealth; }
    int GetCurrentHealth() const {return currHealth; }
    int GetBaseDamage() const { return baseDmg; }
    int GetBuffedDamage() const { return dmgBuff; }
    int GetTotalDamage() const { return totalDmg; }
    int GetXPWorth() const { return pow(level, 2) +  pow(dmgBuff, 3); }

    // manage inventory
    bool AddItem(Item item);
    bool AddItem(Backpack item);
    bool AddItem(Weapon item);
    bool AddItem(Consumable item);
    bool RemoveItem(string itemName);
    bool HasItem(string itemName);
    void ClearInventory();

    // use, equip, and unequip items
    void UseConsumable(string itemName);
    bool EquipItem(string itemName);
    bool UnequipItem(string itemName);

    // combat
    void TakeDamage(int damage);

protected:
    string name;
    int level;
    void SetHealthAndDamage(float healthPercent);

    int maxHealth;
    int currHealth;

    int baseDmg;
    float dmgBuff;
    int totalDmg;
    void UpdateTotalDamage() { totalDmg = baseDmg * dmgBuff;  }

    Inventory inventory;
};

#endif //DUNGEON_CRAWLER_CREATURE_H
