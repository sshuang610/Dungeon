#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Item;
class Poison;
class Room;

class Player: public GameCharacter
{
private:
    int hunger;
    int thirst;
    Poison* poison;
    Room* currentRoom;
    Room* previousRoom;
    vector<Item> inventory;
public:
    Player();
    Player(string);
    void addItem(Item);
    void removeItem(int);
    void increaseStates(int,int,int);
    void changeRoom(Room*);
    bool checkPoison();

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object*);
    void openBag();

    /* Set & Get function*/
    void setHunger(int);
    void setThirst(int);
    void setPoison(Poison*);
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInventory(vector<Item>);
    Room* getCurrentRoom();
    Room* getPreviousRoom();
    vector<Item> getInventory();
    int getHunger();
    int getThirst();
    Poison* getPoison();
};

#endif // PLAYER_H_INCLUDED
