#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

#include "GameCharacter.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <cstdlib>
#include "Player.h"
#include "Room.h"
#include "Monster.h"
#include "NPC.h"
#include "Item.h"
#include "Object.h"
#include "Environment.h"

using namespace std;

class Dungeon{
private:
    Player player;
    vector<Room> rooms;
public:
    Dungeon();
    /* Create a new player, and give him/her basic status */
    void createPlayer();

    /* Create a map, which include several different rooms */
    void createMap();

    /* Deal with player's moveing action */
    void handleMovement();

    /* Deal with player's iteraction with objects in that room */
    bool handleEvent(Object*);

    /* Deal with all game initial setting       */
    /* Including create player, create map etc  */
    void startGame();

    /* Deal with the player's action     */
    /* including showing the action list */
    /* that player can do at that room   */
    /* and dealing with player's input   */
    void chooseAction(vector<Object*>);

    /* Check whether the game should end or not */
    /* Including player victory, or he/she dead */
    bool checkGameLogic();

    void checkHungerAndThirst();

    /* Deal with the whole game process */
    void runDungeon();
};


#endif // DUNGEON_H_INCLUDED
