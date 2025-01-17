//
// Created by meagh on 5/10/2024.
//

#include "Creature.h"

/**
 * Default constructor.
 **/
Creature::Creature() {
    name = "NAMELESS CREATURE";
    level = 1;

    maxHealth = 10;
    currHealth = maxHealth;

    baseDmg = 5;
    dmgBuff = 1;
    totalDmg = baseDmg;
}


/**
 * Constructor for a default Level 1 creature with a custom name.
 *
 * @param name   the creature's name
 **/
Creature::Creature(std::string name) {
    // Resources = 15 x Level 1 = 15
    this->name = name;
    StandardizeName(this->name);
    level = 1;

    maxHealth = 10;
    currHealth = maxHealth;

    baseDmg = 5;
    dmgBuff = 1;
    totalDmg = baseDmg;
}

/**
 * Constructor to make a custom creature Level 1.
 *
 * @param name            name of creature
 * @param healthPercent   the percent of resources health should take
 * @post inventory slots set to 5
 **/
Creature::Creature(string name, float healthPercent) {
    this->name = name;
    StandardizeName(this->name);
    level = 1;
    dmgBuff = 1;
    SetHealthAndDamage(healthPercent);
    currHealth = maxHealth;
}

/**
 * Constructor to make a custom creature.
 *
 * @param name            name of creature
 * @param healthPercent   the percent of resources health should take
 * @param level           the level of the creature
 * @post inventory slots set to 5
 */
Creature::Creature(string name, float healthPercent, int level) {
    this->name = name;
    StandardizeName(this->name);
    if (level < 1) {
        this->level = 1;
    }
    else {
        this->level = level;
    }
    dmgBuff = 1;
    SetHealthAndDamage(healthPercent);
    currHealth = maxHealth;
}

/**
 * Set health and damage of creature based on level.
 *
 * @param healthPercent   the percent of resources health should take
 * @pre health is already to set to initial desired value
 *      (may or may not follow rules)
 **/
void Creature::SetHealthAndDamage(float healthPercent) {
    int resources = 15 * level * pow(1.1, level);
    if (healthPercent < .75) {
        healthPercent = .75;
    }
    else if (healthPercent > .9) {
        healthPercent = .9;
    }
    maxHealth = resources * healthPercent;
    baseDmg = resources - maxHealth; // remaining resources
    UpdateTotalDamage();
}

/**
 * Set a creature's name.
 *
 * @param name the name of the creature
 **/
void Creature::SetName(std::string name) {
    this->name = name;
    StandardizeName(this->name);
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
 * @post consumable's health restore is added to creature
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
    if (currHealth < 0) {
        currHealth = 0;
    }
}

/**
 * Write the creature's info.
 *
 * @param out       the stream to write to
 * @param creature  the creature whose info to write
 * @return the stream written to
 **/
ostream& operator<<(ostream &out, const Creature& creature) {
    out << setw(100) << setfill('-') << left << creature.name + " - " + creature.PrintLevel() + " " << endl
        << creature.PrintHealth() << endl
        << creature.PrintTotalDamage() << endl
        << creature.PrintXP() << endl
        << setw(100) << setfill('_') << "" << endl << endl;

    return out;
}

/**
 * Functions used to get printable version of stats.
 *
 * @return a line of this format: "STAT_NAME: stat_info"
 **/
 string Creature::PrintLevel() const {
    return "Level " + to_string(level);
 }
string Creature::PrintHealth() const {
    return "Health: " + ConvertNumberStatToString(currHealth) + "/" + ConvertNumberStatToString(maxHealth) + " HP";
}
string Creature::PrintBaseDamage() const {
    return "Base Damage: " + ConvertNumberStatToString(baseDmg);
}
string Creature::PrintTotalDamage() const {
    return "Total Damage: " + ConvertNumberStatToString(totalDmg);
}
string Creature::PrintInventory() const {
     stringstream ss;
     ss << inventory;
     string inventoryPrint = ss.str();
     inventoryPrint.pop_back(); // remove last endline
     return inventoryPrint;
 }
 string Creature::PrintXP() const {
     return "Worth " +  ConvertNumberStatToString(GetXPWorth()) + " XP when defeated";
 }
