//
// Created by meagh on 5/10/2024.
//

#ifndef DUNGEON_CRAWLER_ITEM_H
#define DUNGEON_CRAWLER_ITEM_H

#include "BasicFunctions.h"
using namespace std;

class Item : protected BasicFunctions {
public:
    Item();
    Item(string name);
    Item(string name, string description);
    Item(string name, string description, int goldWorth);

    friend ostream& operator<<(ostream& out, const Item& item);

    string GetName() const { return name; }
    char GetType() const { return 'i'; }
    void SetName(string name);
    string GetDescription() { return description; }
    void SetDescription(string description);
    int GetGoldWorth() const { return goldWorth; }


protected:
    string name;
    string description;

    int goldWorth;
};


#endif //DUNGEON_CRAWLER_ITEM_H
