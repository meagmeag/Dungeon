//
// Created by meagh on 5/10/2024.
//

#include "Backpack.h"
using namespace std;

/**
 * Default Constructor
 **/
Backpack::Backpack() {
    name = "UNNAMED BACKPACK";
    description = "Not much to say about this backpack.";
    goldWorth = 0;
    inventorySlots = 1;
}

/**
 * Constructor for a default backpack with a custom name.
 *
 * @param name   the name of the backpack
 **/
Backpack::Backpack(string name) {
    this->name = name;
    StandardizeName(name);
    description = "Not much to say about this backpack.";
    goldWorth = 0;
    inventorySlots = 1;
}

/**
 * Constructor for a default backpack with a custom name and description.
 *
 * @param name             the name of the backpack
 * @param description      a description of the backpack
 **/
Backpack::Backpack(string name, string description) {
    this->name = name;
    StandardizeName(this->name);
    this->description = description;
    StandardizeDescription(this->description);
    goldWorth = 0;
    inventorySlots = 1;
}

/**
 * Constructor for a custom backpack.
 *
 * @param name             the name of the backpack
 * @param description      a description of the backpack
 * @param goldWorth        the backpack's worth in gold
 * @param inventorySlots   the number of inventory slots the backpack adds to user when equipped
 */
Backpack::Backpack(string name, string description, int goldWorth, int inventorySlots) {
    this->name = name;
    StandardizeName(this->name);
    this->description = description;
    StandardizeDescription(this->description);
    this->goldWorth = goldWorth;
    this->inventorySlots = inventorySlots;
}

/**
 * Write the name, description worth, and inventory slots of backpack.
 *
 * @param out   the stream to write to
 * @param item  the backpack to write
 * @return the stream written to
 **/
ostream& operator<<(ostream& out, const Backpack& item) {
    out << static_cast<Item> (item)
        << "\tAdds " << item.inventorySlots << " inventory slot";
    if (item.inventorySlots > 1) { // add s if 2+ slots
        cout << "s";
    }
    cout << " when equipped." << endl;

    return out;
}

