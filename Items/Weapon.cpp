//
// Created by meagh on 5/10/2024.
//

#include "Weapon.h"
using namespace std;

/**
 * Default constructor.
 **/
Weapon::Weapon() {
    name = "PRETTY WEAK WEAPON";
    description = "I guess it works in a pinch.";
    goldWorth = 0;
    dmgBuff = 1.5;
}

/**
 * A constructor for a default weapon with a custom name.
 *
 * @param name    the name of the weapon
 */
Weapon::Weapon(string name) {
    this->name = name;
    StandardizeName(this->name);
    description = "I guess it works in a pinch.";
    goldWorth = 0;
    dmgBuff = 1.5;
    StandardizeDamageBuff();
}


/**
 * Constructor for a default weapon with custom name and description.
 *
 * @param name          the name of the weapon
 * @param description   q description of the weapon
 **/
Weapon::Weapon(string name, string description) {
    this->name = name;
    StandardizeName(this->name);
    this->description = description;
    StandardizeDescription(this->description);
    goldWorth = 0;
    dmgBuff = 1.5;
    StandardizeDamageBuff();
}

/**
 * Constructor for a custom weapon.
 *
 * @param name          the name of the weapon
 * @param description   q description of the weapon
 * @param goldWorth     the weapon's worth in gold
 * @param dmgBuff       the factor a user's attack damage is multiplied by when weapon is equipped
 **/
Weapon::Weapon(string name, string description, int goldWorth, float dmgBuff) {
    this->name = name;
    StandardizeName(this->name);
    this->description = description;
    StandardizeDescription(this->description);
    this->goldWorth = goldWorth;
    this->dmgBuff = dmgBuff;
    StandardizeDamageBuff();
}

/**
 * Write the name, description, worth, and damage buff of weapon.
 *
 * @param out   the stream to write to
 * @param item  the weapon to write
 * @return the stream written to
 **/
ostream& operator<<(ostream& out, const Weapon& item) {
    out << static_cast<Item> (item)
        << "    Multiplies attack damage by " << item.dmgBuff << " when equipped." << endl;

    return out;
}

/**
 * Make sure damage buff is within range (1 - 10)
 **/
void Weapon::StandardizeDamageBuff() {
    if (dmgBuff > 10) {
        dmgBuff = 10;
    }
    else if (dmgBuff < 1) {
        dmgBuff = 1;
    }
}