//
// Created by meagh on 5/11/2024.
//

#include "Consumable.h"
using namespace std;

/**
 * Default constructor.
 **/
Consumable::Consumable() {
    name = "USELESS CONSUMABLE";
    description = "Is this... water???";
    useDescription = "You drink the water. Mmm refreshing!";
    goldWorth = 0;
    dmgBuff = 0;
    numRounds = 0;
    hpRestore = 0;
}

/**
 * Constructor for a consumable that enhances attack damage.
 *
 * @param name             the name of the consumable
 * @param description      a description of the consumable
 * @param goldWorth        the consumable's worth in gold
 * @param useDescription   a description of how the consumable is consumed in the first person
 * @param dmgBuff          the factor a user's attack damage is multiplied by when consumable is consumed
 * @param numRounds        the number of rounds damage is buffed for
 **/
Consumable::Consumable(string name, string description, int goldWorth, string useDescription, float dmgBuff, int numRounds) {
    this->name = name;
    StandardizeName(this->name);
    this->description = description;
    StandardizeDescription(this->description);
    this->useDescription = useDescription;
    StandardizeDescription(this->useDescription);
    this->dmgBuff = dmgBuff;
    this->numRounds = numRounds;
    hpRestore = 0;
}

/**
 * Constructor for a consumable that restores health.
 *
 * @param name             the name of the consumable
 * @param description      a description of the consumable
 * @param goldWorth        the consumable's worth in gold
 * @param useDescription   a description of how the consumable is consumed in the first person
 * @param hpRestore        the amount of HP restored when consumed
 **/
Consumable::Consumable(string name, string description, int goldWorth, string useDescription, int hpRestore) {
    this->name = name;
    StandardizeName(this->name);
    this->description = description;
    StandardizeDescription(this->description);
    this->useDescription = useDescription;
    StandardizeDescription(this->useDescription);
    this->hpRestore = hpRestore;
    dmgBuff = 1;
    numRounds = 0;
}

/**
 * Write the name, description worth, and effect of consumable.
 *
 * @param out   the stream to write to
 * @param item  the consumable to write
 * @return the stream written to
 **/
ostream& operator<<(ostream& out, const Consumable& item) {
    out << static_cast<Item> (item);

    if (item.dmgBuff > 1) {
        out << "\tMultiplies attack damage by " << item.dmgBuff << " for " << item.numRounds <<  " rounds when consumed." << endl;
    }
    else if (item.hpRestore > 0) {
        out << "\tRestores " << item.hpRestore << " HP when consumed." << endl;
    }

    return out;
}