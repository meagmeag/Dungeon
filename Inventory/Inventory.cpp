//
// Created by meagh on 5/10/2024.
//

#include "Inventory.h"
using namespace std;

/**
* Starting inventory constructor. (Five slots.)
**/
Inventory::Inventory() {
    firstSlot = nullptr;
    lastSlot = nullptr;
    leftHandSlot = nullptr;
    rightHandSlot = nullptr;
    backpackSlot = nullptr;
    baseSlots = 5;
    extraSlots = 0;
    totalSlots = baseSlots;
    numItems = 0;
}

/**
 * Destructor
 **/
 Inventory::~Inventory(){
     ClearInventory();
 }

/**
 * Add an item to the inventory.
 *
 * @param item   the item to add
 * @return a bool indicating if item was added
 **/
bool Inventory::AddItem(Item item) {
    if (numItems == totalSlots) { // no available slots
        return false;
    }

    // else, slots available
    InventorySlot* slot = new InventorySlot;
    if (!slot) {
        return false; // no space allocated
    }
    slot->thisItem = new Item;
    *(slot->thisItem) = item;
    slot->name = item.GetName();

    if (!firstSlot) {
        firstSlot = slot;
        lastSlot = slot;
    }
    else {
        lastSlot->nextSlot = slot;
        slot->prevSlot = lastSlot;
        lastSlot = slot;
    }

    numItems++;
    return true;
}
bool Inventory::AddItem(Backpack item) {
    if (numItems == totalSlots) { // no available slots
        return false;
    }

    // else, slots available
    InventorySlot* slot = new InventorySlot;
    if (!slot) {
        return false; // no space allocated
    }
    slot->thisBackpack = new Backpack;
    *(slot->thisBackpack) = item;
    slot->name = item.GetName();

    if (!firstSlot) {
        firstSlot = slot;
        lastSlot = slot;
    }
    else {
        lastSlot->nextSlot = slot;
        slot->prevSlot = lastSlot;
        lastSlot = slot;
    }

    numItems++;
    return true;
}
bool Inventory::AddItem(Weapon item) {
    if (numItems == totalSlots) { // no available slots
        return false;
    }

    // else, slots available
    InventorySlot* slot = new InventorySlot;
    if (!slot) {
        return false; // no space allocated
    }
    slot->thisWeapon = new Weapon;
    *(slot->thisWeapon) = item;
    slot->name = item.GetName();

    if (!firstSlot) {
        firstSlot = slot;
        lastSlot = slot;
    }
    else {
        lastSlot->nextSlot = slot;
        slot->prevSlot = lastSlot;
        lastSlot = slot;
    }

    numItems++;
    return true;
}
bool Inventory::AddItem(Consumable item) {
    if (numItems == totalSlots) { // no available slots
        return false;
    }

    // else, slots available
    InventorySlot* slot = new InventorySlot;
    if (!slot) {
        return false; // no space allocated
    }
    slot->thisConsumable = new Consumable;
    *(slot->thisConsumable) = item;
    slot->name = item.GetName();

    if (!firstSlot) {
        firstSlot = slot;
        lastSlot = slot;
    }
    else {
        lastSlot->nextSlot = slot;
        slot->prevSlot = lastSlot;
        lastSlot = slot;
    }

    numItems++;
    return true;
}

/**
 * Add a weapon or backpack that already exists.
 * (Use for moving item from equipped slot back to inventory.)
 *
 * @param item    the address of the item to add
 * @return a bool indicating if item was added to inventory successfully
 */
bool Inventory::AddItem(Backpack* item) {
    if (numItems + 1 > totalSlots) { // no available slots
        return false;
    }

    // else, slots available
    InventorySlot* slot = new InventorySlot;
    if (!slot) {
        return false; // no space allocated
    }
    slot->thisBackpack = item;
    slot->name = item->GetName();

    if (!firstSlot) {
        firstSlot = slot;
        lastSlot = slot;
    }
    else {
        lastSlot->nextSlot = slot;
        slot->prevSlot = lastSlot;
        lastSlot = slot;
    }

    numItems++;
    return true;
}
bool Inventory::AddItem(Weapon* item) {
    if (numItems + 1 > totalSlots) { // no available slots
        return false;
    }

    // else, slots available
    InventorySlot* slot = new InventorySlot;
    if (!slot) {
        return false; // no space allocated
    }
    slot->thisWeapon = item;
    slot->name = item->GetName();

    if (!firstSlot) {
        firstSlot = slot;
        lastSlot = slot;
    }
    else {
        lastSlot->nextSlot = slot;
        slot->prevSlot = lastSlot;
        lastSlot = slot;
    }

    numItems++;
    return true;
}

/**
 * Remove an item whose existence/slot is unknown from the inventory
 * or equipped items (in that order).
 *
 * @param itemName   the name of the item to remove
 * @return a bool indicating if the removal was successful
 **/
bool Inventory::RemoveItem(string itemName) {
    StandardizeName(itemName);
    InventorySlot* slot = nullptr;

    FindItem(itemName, slot);
    if (slot) { // in regular inventory
        if (slot == firstSlot) {
            firstSlot = slot->nextSlot;
        }
        if (slot == lastSlot) {
            lastSlot = slot->prevSlot;
        }
        if (slot->prevSlot) {
            slot->prevSlot->nextSlot = slot->nextSlot;
        }
        if (slot->nextSlot) {
            slot->nextSlot->prevSlot = slot->prevSlot;
        }

        numItems--;

        // delete slot's content then slot itself
        delete slot->thisItem;
        delete slot->thisConsumable;
        delete slot->thisWeapon;
        delete slot->thisBackpack;
        delete slot;
        return true;
    }

    // not in regular inventory, check equipped slots
}

/**
 * Remove a slot from the inventory without deleting the item in it.
 *
 * @param slot
 * @return
 **/
bool Inventory::RemoveSlotOnly(InventorySlot *slot) {
    if(!slot) {
        return false;
    }

    if (slot == firstSlot) {
        firstSlot = slot->nextSlot;
    }
    if (slot == lastSlot) {
        lastSlot = slot->prevSlot;
    }
    if (slot->prevSlot) {
        slot->prevSlot->nextSlot = slot->nextSlot;
    }
    if (slot->nextSlot) {
        slot->nextSlot->prevSlot = slot->prevSlot;
    }

    delete slot;
    numItems--;
    return true;
}

/**
 * Find the location of an item and its type.
 *
 * @param itemName   the name of the item to find
 * @param slot       an inventory slot pointer to set as the location of the item
 * @return the item type:
 *         - for nonexistent item, w for weapon, c for consumable, b for backpack,
 *         or 'i' for other item
 **/
char Inventory::FindItem(string itemName, InventorySlot* &slot) {
    StandardizeName(itemName);
    slot = firstSlot;

    while (slot) {
        if (slot->name == itemName) {
            if (slot->thisWeapon) {
                return 'w';
            }
            if (slot->thisConsumable) {
                return 'c';
            }
            if (slot->thisBackpack) {
                return 'b';
            }
            if (slot->thisItem) {
                return 'i';
            }
        }
        slot = slot->nextSlot;
    }

    return '-';
}

/**
 * Check if item is in inventory or equipped.
 *
 * @param itemName   the name of the item to check for
 * @return a bool indicating if the item is in inventory or equipped
 **/
bool Inventory::HasItem(string itemName) {
    StandardizeName(itemName);

    // check if equipped
    if ((rightHandSlot && itemName == rightHandSlot->GetName()) || (leftHandSlot && itemName == leftHandSlot->GetName())
        || (backpackSlot && itemName == backpackSlot->GetName())) {
        return true;
    }

    InventorySlot* slot = firstSlot;
    while (slot) {
        if (slot->name == itemName) {
            return true;
        }
        slot = slot->nextSlot;
    }

    return false;
}

/**
 * Delete all items in inventory.
 **/
void Inventory::ClearInventory() {
    InventorySlot* walk = firstSlot;
    InventorySlot* nextWalk = nullptr;

    // walk through items and delete them
    while (walk) {
        nextWalk = walk->nextSlot;
        delete walk->thisItem;
        delete walk->thisConsumable;
        delete walk->thisWeapon;
        delete walk->thisBackpack;
        delete walk;
        numItems--;
        walk = nextWalk;
    }

    firstSlot = nullptr;
    lastSlot = nullptr;
}

/**
 * Equip a weapon.
 *
 * @param slot           an inventory slot pointer holding the item's address
 * @param creatDmgBuff   the creature's dmgBuff
 * @return a bool indicating if the weapon was equipped
 * @post if successful, weapon is put into left hand slot or right hand slot (in that order)
 *       and removed from regular inventory
 **/
bool Inventory::EquipWeapon(InventorySlot* &slot, float& creatDmgBuff) {
    if (!slot || !slot->thisWeapon) {
        return false;
    }

    if (!leftHandSlot) { // left hand slot open
        leftHandSlot = slot->thisWeapon;
    }
    else if (!rightHandSlot) { // right hand slot open
        rightHandSlot = slot->thisWeapon;
    }
    else { // both hands full
        return false;
    }
    creatDmgBuff *= slot->thisWeapon->GetDamageBuff(); // add buff to creature's damage buff

    // delete slot, but not weapon
    RemoveSlotOnly(slot);

    return true;
}

/**
 * Unequip a weapon and return to inventory.
 *
 * @param itemName       the name of the weapon
 * @param creatDmgBuff   the creature's dmgBuff
 * @return a bool indicating if the weapon was unequipped
 * @post if successful, weapon is put back into inventory
 **/
bool Inventory::UnequipWeapon(string itemName, float &creatDmgBuff) {
    if (numItems + 1 > totalSlots) { // cannot unequip bc no room in inventory
        return false;
    }

    StandardizeName(itemName);
    // find which hand it is in, remove buff from creature, and add item back to inventory, removing from hand
    if (leftHandSlot && leftHandSlot->GetName() == itemName) {
        creatDmgBuff /= leftHandSlot->GetDamageBuff();
        AddItem(leftHandSlot);
        leftHandSlot = nullptr;
        return true;
    }
    else if (rightHandSlot && rightHandSlot->GetName() == itemName) {
        creatDmgBuff /= rightHandSlot->GetDamageBuff();
        AddItem(rightHandSlot);
        rightHandSlot = nullptr;
        return true;
    }

    return false; // not in any hand
}

/**
 * Equip a backpack (does not swap).
 *
 * @param slot           an inventory slot pointer holding the item's address
 * @return a bool indicating if the backpack was equipped
 * @post if successful, backpack is put into backpack slot and removed from regular inventory
 */
bool Inventory::SimpleEquipBackpack(InventorySlot* &slot) {
    if (backpackSlot) { // already wearing backpack
        return false;
    }
    if (!slot || !slot->thisBackpack ) {
        return false;
    }

    backpackSlot = slot->thisBackpack;
    extraSlots += slot->thisBackpack->GetInventorySlots();
    UpdateInventorySlots();

    // delete slot, but not backpack
    RemoveSlotOnly(slot);

    return true;
}

/**
 * Equip a backpack (swaps current backpack if necessary).
 *
 * @param slot
 * @return
 **/
bool Inventory::EquipBackpack(InventorySlot *&slot) {
    if (!slot || !slot->thisBackpack || numItems > baseSlots + slot->thisBackpack->GetInventorySlots()) {
        return false;
    }

    if (backpackSlot) {
        AddItem(backpackSlot);
        backpackSlot = slot->thisBackpack;
        extraSlots = backpackSlot->GetInventorySlots();
        UpdateInventorySlots();
        RemoveSlotOnly(slot);
        return true;
    }
    else {
        SimpleEquipBackpack(slot);
        return true;
    }
}

/**
 * Unequip a backpack and return it to inventory.
 *
 * @return a bool indicating if unequip was successful
 */
bool Inventory::UnequipBackpack() {
    if (numItems + 1 > baseSlots) { // must have room for backpack once removed
        return false;
    }

    if (backpackSlot) {
        extraSlots -= backpackSlot->GetInventorySlots();
        AddItem(backpackSlot);
        UpdateInventorySlots();
        backpackSlot = nullptr;
    }

    return false;
}

/**
 * Get the name of the item in the left hand slot.
 *
 * @return the name or an empty string if slot is empty
 **/
string Inventory::GetLeftHandSlotName() const {
    if (leftHandSlot) {
        return leftHandSlot->GetName();
    }

    return "";
}

/**
 * Get the name of the item in the right hand slot.
 *
 * @return the name or an empty string if slot is empty
 **/
string Inventory::GetRightHandSlotName() const {
    if (rightHandSlot) {
        return rightHandSlot->GetName();
    }

    return "";
}

/**
 * Get the name of the item in the backpack slot.
 *
 * @return the name or an empty string if slot is empty
 **/
string Inventory::GetBackpackSlotName() const {
    if (backpackSlot) {
        return backpackSlot->GetName();
    }

    return "";
}

/**
 * Write items in inventory.
 *
 * @param out            the stream to write to
 * @param inventory      the inventory to write
 * @return the stream written to
 **/
ostream& operator<<(ostream& out, const Inventory& inventory) {
    out << "Inventory: " << inventory.numItems << "/" << inventory.totalSlots << " slots used" << endl;
    InventorySlot* walk = inventory.firstSlot;
    int itemNum = 1;

    // walk through items in inventory
    while (walk) {
        out << itemNum << ". ";
        // determine item type and print
        if (walk->thisItem) {
            out << *(walk->thisItem);
        }
        else if (walk->thisBackpack) {
            out << *(walk->thisBackpack);
        }
        else if (walk->thisWeapon) {
            out << *(walk->thisWeapon);
        }
        else if (walk->thisConsumable) {
            out << *(walk->thisConsumable);
        }
        else {
            cout << "ERROR: item number " << itemNum << " has no item!" << endl;
            break;
        }

        itemNum++;
        walk = walk->nextSlot;
    }
    out << endl << endl;

    // print equipped item
    if (inventory.leftHandSlot) {
        out << "Left hand holding: " << endl
            << *inventory.leftHandSlot << endl;
    }
    else {
        out << "Left hand holding nothing." << endl << endl;
    }

    if (inventory.rightHandSlot) {
        out << "Right hand holding: " << endl
            << *inventory.rightHandSlot << endl;
    }
    else {
        out << "Right hand holding nothing." << endl << endl;
    }

    if (inventory.backpackSlot) {
        out << "Wearing: " << endl
            << *inventory.backpackSlot << endl;
    }
    else {
        out << "Wearing no backpack." << endl;
    }

    return out;
}