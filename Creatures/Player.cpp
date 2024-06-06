//
// Created by meagh on 5/11/2024.
//

#include "Player.h"

/**
 * Default constructor.
 **/
Player::Player() {
    name = "UNNAMED PLAYER";
    // other member variables follow default player constructor
}

/**
 * Constructor for player with custom name.
 * @param name
 **/
Player::Player(std::string name) {
    this->name = name;
    StandardizeName(this->name);
}

/**
 * Write all of the player's stats.
 *
 * @param out      the stream to write to
 * @param player   the player to write
 * @return the stream written to
 */
ostream& operator<<(ostream& out, const Player& player) {
    out << setw(100) << setfill('-') << left << player.name + " - " + player.PrintLevel() + " " << endl
        << player.PrintHealth() << endl
        << player.PrintBaseDamage() << endl
        << player.PrintTotalDamage() << endl << endl
        << player.inventory
        << setw(100) << setfill('_') << "" << endl << endl;

    return out;
}

void Player::LevelUp(int level) {
    this->level = level;
    SetHealthAndDamage(1);
    currHealth = maxHealth;
}