//
// Created by meagh on 5/10/2024.
//

#include "Creature.h"

/**
 * Default constructor.
 **/
Creature::Creature() {
    name = "NAMELESS CREATURE";

    maxHealth = 10;
    currHealth = maxHealth;

    baseDmg = 5;
    dmgBuff = 1;
    totalDmg = baseDmg;
}


/**
 * Constructor for a default creature with a custom name.
 *
 * @param name   the creature's name
 **/
Creature::Creature(std::string name) {
    this->name = name;
    StandardizeName(this->name);

    maxHealth = 10;
    currHealth = maxHealth;

    baseDmg = 5;
    dmgBuff = 1;
    totalDmg = baseDmg;
}

/**
 * Constructor to make a custom creature.
 *
 * @param name     name of creature
 * @param maxHealth   maxHealth of creature
 * @param baseDmg  base attack damage of creature
 * @post inventory slots set to 5
 **/
Creature::Creature(string name, int maxHealth, int baseDmg) {
    this->name = name;
    StandardizeName(this->name);

    this->maxHealth = maxHealth;
    currHealth = maxHealth;

    this->baseDmg = baseDmg;
    dmgBuff = baseDmg;
}

/**
 * Add an item to creature's inventory.
 *
 * @param item    the item to add
 * @return a bool indicating if the item was successfully added to inventory
 **/
bool Creature::AddItem(Item item) {
    return inventory.AddItem(item);
}
bool Creature::AddItem(Backpack item) {
    return inventory.AddItem(item);
}
bool Creature::AddItem(Weapon item) {
    return inventory.AddItem(item);
}
bool Creature::AddItem(Consumable item) {
    return inventory.AddItem(item);
}

/**
 * Remove an item from creature's inventory or equipped items (in that order).
 *
 * @param itemName   the name of the item to remove
 * @return a bool indicating if the removal was successful
 **/
bool Creature::RemoveItem(string itemName) {
    if (inventory.RemoveItem(itemName)) {
        return true;
    }

    // not in main inventory, could be in equipped slots
    if (inventory.UnequipWeapon(itemName, dmgBuff)) { // check if in weapon slots
        return true;
    }
    return inventory.UnequipBackpack(); // check if in backpack slot
}


/**
 * Determine if creature has item in inventory or equipped.
 *
 * @param itemName   the name of the item
 * @return a bool indicating if creature has item
 **/
bool Creature::HasItem(string itemName) {
    StandardizeName(itemName);

    // check equipped slots
    if (inventory.GetLeftHandSlotName() == itemName) {
        return true;
    }
    if (inventory.GetRightHandSlotName() == itemName) {
        return true;
    }
    if (inventory.GetBackpackSlotName() == itemName) {
        return true;
    }

    // if not in equipped slots, check inventory
    return inventory.HasItem(itemName);
}

/**
 * Use consumable.
 *
 * @param itemName   the name of consumable
 * @post health is added to creature
 **/
void Creature::UseConsumable(string itemName) {
    InventorySlot* slot = nullptr;
    char itemType;

    itemType = inventory.FindItem(itemName, slot);
    if (itemType != 'c') { // item exists but is not a consumable
        return;
    }

    currHealth += slot->thisConsumable->GetHPRestored();
    if (currHealth > maxHealth) {
        currHealth = maxHealth;
    }
    inventory.RemoveItem(slot);
}

/**
 * Equip an item in the inventory.
 *
 * @param itemName    the name of the item
 * @return a bool indicating if the item was equipped
 * @post if item's respective slot is available, item is moved from inventory
 *       to slot
 **/
bool Creature::EquipItem(string itemName) {
    InventorySlot* slot = nullptr;
    char itemType;

    itemType = inventory.FindItem(itemName, slot);
    if (itemType == 'w') {
        bool result = inventory.EquipWeapon(slot, dmgBuff);
        UpdateTotalDamage();
        return result;
    }
    if (itemType == 'b') {
        return inventory.EquipBackpack(slot);
    }

    return false; // consumable or other non-equippable item
}

/**
 * Unequip an item and return it to inventory.
 *
 * @param itemName   the name of the item to equip
 * @return a bool indicating if unequip was successful
 **/
bool Creature::UnequipItem(string itemName) {
    if (inventory.UnequipWeapon(itemName, dmgBuff)) { // try to unequip item as a weapon first
        UpdateTotalDamage();
        return true;
    }

    return inventory.UnequipBackpack(); // then try as backpack
}

/**
 * Remove all items from creature's inventory.
 **/
void Creature::ClearInventory() {
    inventory.ClearInventory();
}

/**
 * Apply damage to creature's health.
 *
 * @param damage   the damage dealt to creature
 **/
void Creature::TakeDamage(int damage) {
    currHealth -= damage;
}

/**
 * Write the creature's info.
 *
 * @param out       the stream to write to
 * @param creature  the creature whose info to write
 * @return the stream written to
 **/
ostream& operator<<(ostream &out, const Creature& creature) {
    out << setw(100) << setfill('-') << left << creature.name << endl
        << "Health: " << creature.currHealth << "/" << creature.maxHealth << " HP" << endl
        << "Base Damage: " << creature.baseDmg << endl
        << "Buffed Damage: " << creature.totalDmg << endl << endl
        << creature.inventory
        << setw(100) << setfill('_') << "" << endl << endl;

    return out;
}
