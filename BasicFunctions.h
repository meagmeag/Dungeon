//
// Created by meagh on 5/10/2024.
//

#ifndef DUNGEON_CRAWLER_BASICFUNCTIONS_H
#define DUNGEON_CRAWLER_BASICFUNCTIONS_H


#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

class BasicFunctions {
public:
    void StandardizeName(string& name);
    void StandardizeDescription(string& description);
    bool EndOfSentence(string word);
    void StandardizeGold(int& gold);
};


#endif //DUNGEON_CRAWLER_BASICFUNCTIONS_H
