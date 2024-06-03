//
// Created by meagh on 5/10/2024.
//

#ifndef DUNGEON_CRAWLER_INVENTORY_H
#define DUNGEON_CRAWLER_INVENTORY_H

#include "BasicFunctions.h"
#include <cassert>
#include "Backpack.h"
#include "Weapon.h"
#include "Consumable.h"
// Item.h included through above header files
using namespace std;

struct InventorySlot {
    string name;
    InventorySlot* nextSlot = nullptr;
    InventorySlot* prevSlot = nullptr;

    Item* thisItem = nullptr;
    Backpack* thisBackpack = nullptr;
    Weapon* thisWeapon = nullptr;
    Consumable* thisConsumable = nullptr;

    // inventory slots must point to only ONE item
    void CheckGoodSlot() {
        int numItems = 0;

        if (thisItem) {
            numItems++;
        }
        if (thisBackpack) {
            numItems++;
        }
        if (thisWeapon) {
            numItems++;
        }
        if (thisConsumable) {
            numItems++;
        }

        assert(numItems <= 1);
    }
};

class Inventory : protected  BasicFunctions {
public:
    Inventory();
    ~Inventory();
    friend ostream& operator<<(ostream& out, const Inventory& inventory);

    int GetInventorySlots() const { return totalSlots; }
    int GetNumItems() const { return numItems; }

    // managing inventory
    bool AddItem(Item item);
    bool AddItem(Backpack item);
    bool AddItem(Backpack* item);
    bool AddItem(Weapon item);
    bool AddItem(Weapon* item);
    bool AddItem(Consumable item);
    bool RemoveItem(string itemName);
    void ClearInventory();
    char FindItem(string itemName, InventorySlot* &slot);
    bool HasItem(string itemName);

    // equipping/unequipping items and using consumables
    bool EquipWeapon(InventorySlot* &slot, float& creatDmgBuff);
    bool UnequipWeapon(string itemName, float& creatDmgBuff);
    bool EquipBackpack(InventorySlot* &slot);
    bool UnequipBackpack(string itemName);
    string GetRightHandSlotName() const;
    string GetLeftHandSlotName() const;
    string GetBackpackSlotName() const;

private:
    // unequipped inventory
    InventorySlot* firstSlot;
    InventorySlot* lastSlot;

    // equipped inventory
    Weapon* leftHandSlot;
    Weapon* rightHandSlot;
    Backpack* backpackSlot;

    // private inventory management

    int baseSlots;
    int extraSlots;
    int totalSlots;
    int numItems;

    void UpdateInventorySlots() { totalSlots = baseSlots + extraSlots; }
    bool RemoveSlotOnly(InventorySlot* slot);
};


#endif //DUNGEON_CRAWLER_INVENTORY_H
