//
// Created by meagh on 6/4/2024.
//

#include "Game.h"

Game::Game(): player("unknown"), goblin("goblin") {}

void Game::Run() {
    Intro();
}

void Game::NextDialogue() {
    cout << endl << "(press enter to continue)" << endl;
    getline(cin, input);
    cout << setw(10) << setfill('-') << left << "" << endl;
}

/**
 * Get the player name and print their stats.
 **/
void Game::GetPlayerName() {
    cout << "What is your name? (type first name, then press enter)" << endl;
    cin >> input;
    player.SetName(input);
    cout << "Is " << player.GetName() << " right? (enter y or n)" << endl;
    cin >> input;
    while (input.at(0) != 'y') {
        cout << "Let me ask again, then." << endl
        << "What is your name? (type first name, then press enter)" << endl;
        cin >> input;
        player.SetName(input);
        cout << "Is " << player.GetName() << " right? (type y or n, then press enter)" << endl;
        cin >> input;
    }
    cout << endl << "Nice to meet you, " << player.GetName() << endl << endl;
    getline(cin, input); // eat blank
}

/**
 * Get the player's name then teach them about inventory, weapons and equipping.
 **/
void Game::Intro() {
    GetPlayerName();
    cout << "This is you... (press enter to see stats)" << endl;
    getline(cin, input);
    cout << player;
    NextDialogue();
    cout << "You can see your stats at any time by typing " << Quote("show me") << " and pressing enter." << endl
        << "Try it now." << endl;
    getline(cin, input);
    while (input != "show me") {
        cout << "Try again. Type " << Quote("show me") << " and press enter" << endl;
        getline(cin,input);
    }
    cout << endl << player;
    NextDialogue();
    cout << "Nice! Moving on..." << endl;
    NextDialogue();
    cout << Quote(player.PrintHealth()) << endl
        << "This line shows your health. Don't let it reach zero, or you'll DIE!" << endl << endl
        << "Hmm.. Full health. It seems you haven't seen combat yet." << endl
        << "I have a feeling that will change..." << endl;
    NextDialogue();
    cout << Quote(player.PrintBaseDamage()) << endl
        << "This line shows your base damage, which is based on your level." << endl << endl
        << "Don't worry weakling, it will increase as you level up..." << endl;
    NextDialogue();
    cout << Quote(player.PrintBuffedDamage()) << endl
        << "This line shows your buffed damage." << endl
        << "That is your base damage times any buffs given by your weapons (which will be explained further later)." << endl << endl
        << "Seeing as you have no weapons currently, it's the same as your base damage." << endl;
    NextDialogue();
    cout << Quote(player.PrintInventory()) << endl << endl
        << "All that is your inventory: what you are carrying and what weapons and backpack you have equipped." << endl
        << "You have nothing now, but you shall soon have much..." << endl;
    NextDialogue();
}