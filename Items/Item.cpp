//
// Created by meagh on 5/10/2024.
//

#include "Item.h"
using namespace std;


/**
 * Default Constructor
 **/
Item::Item() {
    name = "USELESS ITEM";
    description = "A very ambiguous looking item...";
    goldWorth = 0;
}

/**
 * A constructor for a default item with a custom name.
 *
 * @param name   the name of the item.
 **/
Item::Item(string name) {
    this->name = name;
    StandardizeName(this->name);
    description = "A very ambiguous looking item...";
    goldWorth = 0;
}

/**
 * A constructor for an item worth 0 gold but with a custom
 * name and description.
 *
 * @param name             the name of the item
 * @param description      a description of the item
 */
Item::Item(string name, string description) {
    this->name = name;
    StandardizeName(this->name);
    this->description = description;
    StandardizeDescription(this->description);
    goldWorth = 0;
}

/**
 * Constructor to make a custom item.
 *
 * @param name             the name of the item
 * @param description      a description of the item
 * @param goldWorth        the worth of the item in gold
 * @pre goldWorth is >= 0 (if not, it will be set to 0)
 */
Item::Item(string name, string description, int goldWorth) {
    this->name = name;
    StandardizeName(this->name);
    this->description = description;
    StandardizeDescription(this->description);
    this->goldWorth = goldWorth;
}

/**
 * Set the item's name.
 *
 * @param name   the name of the item
 * @post the name is standardized
 **/
void Item::SetName(string name) {
    this->name = name;
    StandardizeName(this->name);
}

/**
 * Set the item's description.
 *
 * @param description   the description of the item
 * @post the description is standardized
 **/
void Item::SetDescription(string description)
{
    this->description = description;
    StandardizeDescription(this->description);
}

/**
 * Write the name, description and worth of item.
 *
 * @param out   the stream to write to
 * @param item  the item to write
 * @return the stream written to
 **/
ostream& operator<<(ostream& out, const Item& item) {
    out << item.name << endl
        << "    " << item.description << endl
        << "    Worth " << item.ConvertNumberStatToString(item.goldWorth) << " gold." << endl;

    return out;
}

