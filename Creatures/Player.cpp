//
// Created by meagh on 5/11/2024.
//

#include "Player.h"

/**
 * Default constructor.
 **/
Player::Player() {
    name = "UNNAMED PLAYER";
    currXP = 0;
    neededXP = 10;
    // other member variables follow default player constructor
}

/**
 * Constructor for player with custom name.
 * @param name
 **/
Player::Player(std::string name) {
    this->name = name;
    StandardizeName(this->name);
    currXP = 0;
    neededXP = 10;
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
        << player.PrintXP() << endl
        << player.PrintHealth() << endl
        << player.PrintBaseDamage() << endl
        << player.PrintTotalDamage() << endl << endl
        << player.inventory
        << setw(100) << setfill('_') << "" << endl << endl;

    return out;
}

/**
 * Get printable version of XP stats.
 *
 * @return the current and needed XP as a string
 **/
string Player::PrintXP() const {
    return ConvertNumberStatToString(currXP) + "/" + ConvertNumberStatToString(neededXP) + " XP";
}

int Player::GainXP(int XP) {
    currXP += XP;
    if (currXP >= neededXP) {
        return LevelUp();
    }
    return 0;
}

int Player::LevelUp() {
    int numLevels = 0;
    while (currXP >= neededXP) {
        level++;
        numLevels++;
        SetHealthAndDamage(PLAYER_HEALTH_PERCENT);
        currHealth = maxHealth;
        currXP -= neededXP;
        neededXP = pow(level, 2) * 20;
    }
    return numLevels;
}