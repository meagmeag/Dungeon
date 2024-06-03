cmake_minimum_required(VERSION 3.27)
project(Dungeon)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Creatures)
include_directories(Inventory)
include_directories(Items)

add_executable(Dungeon
        Creatures/Creature.cpp
        Creatures/Creature.h
        Creatures/Player.cpp
        Creatures/Player.h
        Inventory/Inventory.cpp
        Inventory/Inventory.h
        Items/Backpack.cpp
        Items/Backpack.h
        Items/Consumable.cpp
        Items/Consumable.h
        Items/Item.cpp
        Items/Item.h
        Items/Weapon.cpp
        Items/Weapon.h
        BasicFunctions.cpp
        BasicFunctions.h
        main.cpp)
