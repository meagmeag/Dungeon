//
// Created by meagh on 6/4/2024.
//

#include "Game.h"

Game::Game(): player("unknown"), goblin("goblin") {}

void Game::Run() {
    GetPlayerName();
}

void Game::GetPlayerName() {
    string input;
    cout << "What is your name?" << endl;
    cin >> input;
    player.SetName(input);
    getline(cin, input); // eat blank
    cout << "Nice to meet you, " << player.GetName() << endl
        << "This is you... (press enter to see stats)";
    getline(cin, input);
    cout << player;
}