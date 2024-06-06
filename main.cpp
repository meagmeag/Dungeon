//
// Created by meagh on 6/4/2024.
//

#include "Game.h"

int main() {
    Player player;
    player.GainXP(player.neededXP + 90);
    cout << player;
    return 0;
}