//
// Created by meagh on 5/10/2024.
//

#ifndef DUNGEON_CRAWLER_INVENTORY_H
#define DUNGEON_CRAWLER_INVENTORY_H

#include "BasicFunctions.h"
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
    bool AddItem(Weapon item);
    bool AddItem(Consumable item);
    bool AddItem(Weapon* item);
    bool AddItem(Backpack* item);
    bool RemoveItem(string itemName);
    bool RemoveItem(InventorySlot* &slot);
    void ClearInventory();
    char FindItem(string itemName, InventorySlot* &slot); // find slot and return item type

    // checking inventory
    bool HasItem(string itemName);
    string GetRightHandSlotName() const;
    string GetLeftHandSlotName() const;
    string GetBackpackSlotName() const;

    // equipping/unequipping items and using consumables
    bool EquipWeapon(InventorySlot* &slot, float& creatDmgBuff);
    bool UnequipWeapon(string itemName, float& creatDmgBuff);
    bool EquipBackpack(InventorySlot* &slot);
    bool UnequipBackpack();

private:
    // unequipped inventory
    InventorySlot* firstSlot;
    InventorySlot* lastSlot;

    // equipped inventory
    Weapon* leftHandSlot;
    Weapon* rightHandSlot;
    Backpack* backpackSlot;

    // private inventory management
    void UpdateInventorySlots() { totalSlots = baseSlots + extraSlots; }  // use after equipping or unequipping backpack
    bool RemoveSlotOnly(InventorySlot* slot); // use after equipping any item
    bool SimpleEquipBackpack(InventorySlot* &slot); // equip backpack without swapping

    // inventory slot numbers
    int baseSlots;
    int extraSlots;
    int totalSlots;
    int numItems;
};


#endif //DUNGEON_CRAWLER_INVENTORY_H
