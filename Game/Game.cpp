//
// Created by meagh on 6/4/2024.
//

#include "Game.h"

/**
 * Constructor
 **/
Game::Game(): player("unknown") {}

/**
 * Run the game.
 **/
void Game::Run() {
    Intro();
}

/**
 * Print a dashed line.
 * Use between dialogue and actions.
 **/
void Game::PrintBreak() const {
    cout << setfill('-') << setw(10) << "" << endl;
}

void Game::PrintPlayer() {
    cout << player;
    NextDialogue();
}

/**
 * Print the player's health and wait for enter to be pressed.
 **/
void Game::PrintPlayerHealth() {
    PrintBreak();
    cout << "Your " << player.PrintHealth() << endl << endl;
    NextDialogue();
}

/**
 * Print the player's inventory and wait for enter to be pressed.
 **/
void Game::PrintPlayerInventory() {
    PrintBreak();
    cout << player.PrintInventory() << endl << endl;
    NextDialogue();
}

/**
 * Re-take user input until it is what is expected
 *
 * @param correctInput
 * @param errorMessage
 **/
void Game::GetCorrectInput(string correctInput, string errorMessage) {
    StandardizeDescription(errorMessage);
    StandardizeName(correctInput);
    getline(cin, input);
    StandardizeName(input);
    while (input != correctInput) {
        cout << errorMessage << endl;
        getline(cin,input);
        StandardizeName(input);
    }
    cout << endl;
}

/**
 * Transition to next dialogue (prompt to press enter).
 **/
void Game::NextDialogue(const string& action) {
    cout << endl << "(press enter to " + action + ")" << endl;
    getline(cin, input);
    PrintBreak();
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
    StandardizeName(input);
    while (input.at(0) != 'Y') {
        cout << "Let me ask again, then." << endl
        << "What is your name? (type first name, then press enter)" << endl;
        cin >> input;
        player.SetName(input);
        cout << "Is " << player.GetName() << " right? (type y or n, then press enter)" << endl;
        cin >> input;
        StandardizeName(input);
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
    PrintPlayer();
    cout << "You can see all of your stats at any time by typing \"show me\" and pressing enter." << endl
        << "Try it now." << endl;
    GetCorrectInput("show me", "That's not right. Try again. Type \"show me\" and press enter.");
    PrintPlayer();
    cout << "Nice! Moving on..." << endl << endl;
    cout << Quote(player.PrintHealth()) << endl
        << "This line shows your health. Don't let it reach zero, or you'll DIE!" << endl << endl
        << "Hmm.. Full health. It seems you haven't seen combat yet." << endl
        << "I have a feeling that will change soon..." << endl;
    NextDialogue();
    cout << Quote(player.PrintBaseDamage()) << endl
        << "This line shows your base damage, which is based on your level." << endl << endl
        << "Don't worry weakling, it will increase as you level up..." << endl;
    NextDialogue();
    cout << Quote(player.PrintTotalDamage()) << endl
        << "This line shows your total damage." << endl
        << "That is your base damage times any buffs given by your weapons (which will be explained further later)." << endl << endl
        << "Seeing as you have no weapons currently, it's the same as your base damage." << endl;
    NextDialogue();
    cout << Quote(player.PrintInventory()) << endl << endl
        << "All that is your inventory: what you are carrying and what weapons and backpack you have equipped." << endl
        << "You have nothing now, but you shall soon have much..." << endl;
    NextDialogue();
    cout << "Who are you, you ask? Prepare to be... disappointed." << endl
        << "You are just a simple plebeian peasant, and a serf at that. You farm, you serve your lord, and you eventually die of the plague." << endl
        << "But it doesn't have to be that way..." << endl;
    NextDialogue();
    cout << "There are knights in your village." << endl
        << "The king lives not far from here, so they stay here for cheap room and board and supplies between battles." << endl
        << "You have always dreamed of being one, but it could never be, right? Maybe not." << endl << endl
        << "Well, it certainly won't happen here, in your pig sty of a house! Get outside!" << endl;
    NextDialogue("go outside");
    cout << "Oh look! A knife on the ground!" << endl << endl
        << "To put an item in your inventory, type \"take ___\", ___ being the item." << endl
        << "Try it on the knife." << endl;
    GetCorrectInput("take knife", "That's not right. Type \"take knife\".");
    player.AddItem(Weapon("knife", "small and not very sharp", 3, 1.7));
    cout << "Let's see what that did to your inventory. Type \"show me\" again." << endl;
    GetCorrectInput("show me", "That's not right. Type \"show me\".");
    PrintPlayer();
    cout << "Look! It's now in your inventory, taking up one slot." << endl
        << "But it's not doing you much good in your inventory. Equip it!" << endl << endl
        << "Type \"equip ___\" to equip an item. Try it on the knife." << endl;
    GetCorrectInput("equip knife", "That's not right. Type \"equip knife\"");
    player.EquipItem("knife");
    cout << "Good, now show your stats again to see what that did." << endl;
    GetCorrectInput("show me", "That's not right. Type \"show me\".");
    PrintPlayer();
    cout << "Your damage is now 5 x 1.7 (the knife's attack damage buff)." << endl
        << "Notice, your total damage is not a decimal - it's a whole number. Damage can only ever be a whole number." << endl;
    NextDialogue();
    cout << "Suddenly, you hear a scream from the local tavern - \"The Jolly Roger's\"!" << endl;
    NextDialogue("run to The Jolly Roger's");
    cout << "As you burst through the door, you see the tavern patrons frozen in their seats." << endl
        << "In the middle of the tavern, walking towards the bar, is a dastardly imp." << endl << endl
        << "You can probably take it..." << endl
        << "Type \"attack ___\" to attack an enemy" << endl;
    GetCorrectInput("attack imp", "That's not right. Type \"attack imp\"");
    SimpleCombat(Creature ("imp"));
    cout << "Nice job! But, that imp still did some serious damage to you. Let's check your health." << endl << endl
        << "Type \"show health\" to see just your health stats." << endl;
    GetCorrectInput("show health", "That's not right. Type \"show health\".");
    PrintPlayerHealth();
    cout << "Ouch! ...Wait! Here comes the barkeep! Maybe he can help you..." << endl;
    NextDialogue("talk to the barkeep");
    cout << "The barkeep approaches you, looking happily relieved." << endl
        << "However, his relieved expression turns to disgust when he realizes you are a simple peasant, not a knight." << endl
        << "\"Here,\" he groans as he slams a WEAK HEALTH POTION down into your hand then grumpily walks away. Not even a thank you?!" << endl << endl
        << "The bar chatter continues. Some patrons are eyeing your WEAK HEALTH POTION... You better put it in your inventory." << endl
        << "Remember, thats the \"take ___\" command" << endl;
    GetCorrectInput("take WEAK HEALTH POTION", "That's not right. type \"take weak health potion\"");
    player.AddItem(Consumable("weak health potion", "a shimmery red liquid in a vial", 5, "You drink it. It tastes bitter, but you feel stronger instantly.", 5));
    cout << "Good. Now type \"show inventory\" to show just your inventory." << endl;
    GetCorrectInput("show inventory", "that's not right. type \"show inventory\"");
    PrintPlayerInventory();
    cout << "Alright, you clearly need the potion. Type \"use ___\" to use a consumable." << endl;
    GetCorrectInput("use weak health potion", "that's not right. type \"use weak health potion\"");
    player.UseConsumable("weak health potion");
    cout << "Now, look at your just your health stats again." << endl
        << "Remember, that's \"show health\"" << endl;
    GetCorrectInput("show health", "That's not right. Type \"show health\".");
    PrintPlayerHealth();
    cout << "See! All better." << endl << endl
        << "You should know that was an easy fight. In the future, it won't be so easy." << endl
        << "You will have more attack abilities and have to put more thought into your actions." << endl
        << "You may find yourself overwhelmed, and you may have to flee!" << endl
        << "In the future, combat will have that option, and it will be explained further." << endl;
    NextDialogue();
}

/**
 * Combat between player and one monster without the option to flee.
 * Use for tutorials.
 *
 * @param monster    The monster for the player to fight.
 **/
void Game::SimpleCombat(Creature monster) {
    PrintBreak();
    while (true) {
        cout << "You do " << player.GetTotalDamage() << " damage to the " << monster.GetName() << endl;
        monster.TakeDamage(player.GetTotalDamage());
        cout << monster.GetName() << "'s " << monster.PrintHealth() << endl << endl;
        if (monster.GetCurrentHealth() <= 0) {
            cout << "You slayed the " << monster.GetName() << "!" << endl << endl;
            break;
        }
        cout << "It does " << monster.GetTotalDamage() << " damage to you " << endl;
        player.TakeDamage(monster.GetTotalDamage());
        cout << "Your " << player.PrintHealth() << endl << endl;
        if (player.GetCurrentHealth() <= 0) {
            cout << "YOU DIED!" << endl << endl;
            break;
        }
        NextDialogue("continue fighting the " + monster.GetName());
    }
    NextDialogue();
}