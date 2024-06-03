//
// Created by meagh on 5/11/2024.
//

#include "Player.h"

/**
 * Default constructor.
 **/
Player::Player() {
    name = "UNNAMED PLAYER";
    // other member variables follow default creature constructor
}

/**
 * Constructor for player with custom name.
 * @param name
 **/
Player::Player(std::string name) {
    this->name = name;
    StandardizeName(this->name);
}