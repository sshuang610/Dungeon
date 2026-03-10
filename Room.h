#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Environment.h"

using namespace std;

class Environment;

class Room
{
private:
    Room *upRoom;
    Room *downRoom;
    Room *leftRoom;
    Room *rightRoom;
    bool isExit;
    int index;
    vector<Object *> objects; /*contain 1 or multiple objects, including monster, npc, etc*/
    Environment *environment;

public:
    Room();
    Room(bool, int, vector<Object *>, Environment *);
    void removeObject(Object *);

    /* Set & Get function*/
    void setUpRoom(Room *);
    void setDownRoom(Room *);
    void setLeftRoom(Room *);
    void setRightRoom(Room *);
    void setIsExit(bool);
    void setIndex(int);
    void setObjects(vector<Object *>);
    void setEnvironment(Environment *);
    bool getIsExit();
    int getIndex();
    vector<Object *> getObjects();
    Environment *getEnvironment();
    Room *getUpRoom();
    Room *getDownRoom();
    Room *getLeftRoom();
    Room *getRightRoom();
};

#endif // ROOM_H_INCLUDED
