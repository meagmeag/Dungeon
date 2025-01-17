//
// Created by meagh on 5/10/2024.
//

#include "GameObject.h"
using namespace std;

/**
 * Standardize a name for printing.

 * @post name is in all caps
 **/
void GameObject::StandardizeName(string& name) {
    for (int i = 0; i < name.length(); i++) {
        name.at(i) = toupper(name.at(i));
    }
}

/**
 * Add commas to a stat.
 *
 * @param stat   the stat to standardize
 * @return the stat as a string with commas
 **/
string GameObject::ConvertNumberStatToString(int stat) const {
    string statString = to_string(stat);
    for (int i = statString.length() - 3; i > 0; i -= 3) {
        statString.insert(i, ",");
    }
    return statString;
}

/**
 * Standardize the description.
 *
 * @param description   the description to standardize
 * @post sentences in description start with a capital ends with a period.
 **/
void GameObject::StandardizeDescription(string& description) {
    istringstream ss(description);
    description = "";
    string curWord;
    bool containedPeriod = false; // or ? or !

    ss >> curWord;
    curWord.at(0) = toupper(curWord.at(0)); // capitalize first word
    containedPeriod = EndOfSentence(curWord);
    description += curWord + " ";

    while(ss >> curWord) { // add words to description
        if (containedPeriod) { // last word was end of sentence
            curWord.at(0) = toupper(curWord.at(0)); // capitalize this word
        }
        description += curWord + " ";
        containedPeriod = EndOfSentence(curWord);
    }

    // get rid of space at end
    if (containedPeriod) { // last word contained period
        description.pop_back(); // simply remove last space
    }
    else { // did not contain period
        description.at(description.length() - 1) = '.'; // add one
    }
}

/**
 * Determine if string is the end of sentence. (Ends with . ? or !)
 *
 * @param word   the word to check
 * @return a bool indicating if above is true
 */
bool GameObject::EndOfSentence(string word) {
        char lastChar = word.at(word.length() - 1);

        if (lastChar == '.' || lastChar == '?' || lastChar == '!') {
            return true;
        }

        return false;
}

/**
 * Standardize gold worth.
 *
 * @post goldWorth is not < 0
 **/
void GameObject::StandardizeGold(int& gold) {
    if (gold < 0) {
        gold = 0;
    }
}

/**
 * Put a string in quotes.
 *
 * @param words  the string to quote
 */
string GameObject::Quote(std::string words) {
    return "\"" + words + "\"";
}