//
// Created by meagh on 5/10/2024.
//

#ifndef DUNGEON_CRAWLER_CREATURE_H
#define DUNGEON_CRAWLER_CREATURE_H

#include "BasicFunctions.h"
#include "Inventory.h"
using namespace std;

class Creature : protected BasicFunctions {
public:
    Creature();
    Creature(string name);
    Creature(string name, int health, int baseDmg);

    friend ostream& operator<<(ostream &out, const Creature& creature);

    // get info
    string GetName() const { return name; }
    int GetMaxHealth() const { return maxHealth; }
    int GetCurrentHealth() const {return currHealth; }
    int GetBaseDamage() const { return baseDmg; }
    int GetBuffedDamage() const { return dmgBuff; }
    int GetTotalDamage() const { return totalDmg; }

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

    int maxHealth;
    int currHealth;

    int baseDmg;
    float dmgBuff;
    int totalDmg;
    void UpdateTotalDamage() { totalDmg = baseDmg * dmgBuff;  }

    Inventory inventory;
};

#endif //DUNGEON_CRAWLER_CREATURE_H
