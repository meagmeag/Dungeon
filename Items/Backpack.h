//
// Created by meagh on 5/10/2024.
//

#ifndef DUNGEON_CRAWLER_BACKPACK_H
#define DUNGEON_CRAWLER_BACKPACK_H

#include "Item.h"
using namespace std;

class Backpack : public Item {
public:
    Backpack();
    Backpack(string name);
    Backpack(string name, string description);
    Backpack(string name, string description, int goldWorth, int inventorySlots);
    friend ostream& operator<<(ostream& out, const Backpack& item);

    char GetType() const {return 'b'; }
    int GetInventorySlots() const { return inventorySlots; }

private:
    int inventorySlots;
};


#endif //DUNGEON_CRAWLER_BACKPACK_H
