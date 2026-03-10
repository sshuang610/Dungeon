#ifndef ENVIRONMENT_H_INCLUDED
#define ENVIRONMENT_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
#include "Item.h"
#include "NPC.h"

using namespace std;

class Room;

class Environment
{
    private:
        int roomIndex;
        string name;
    public:
        Environment();
        Environment(int, string);

        string getName();
        void setName(string);
        int getRoomIndex();
        void setRoomIndex(int);

        virtual void roomSystem(Object*) = 0;
};

class Desert : public Environment
{
    private:
    int sandstormTime=0;
    public:
        Desert();
        Desert(int);
        
        void setSandstormTime(int);
        int getSandstormTime();

        void roomSystem(Object*);
};

class Forest : public Environment
{   
    public:
        Forest();
        Forest(int);

        void roomSystem(Object*);
};

class Swamp : public Environment
{   
    public:
        Swamp();
        Swamp(int);

        void roomSystem(Object* o);
};

class Grassland : public Environment
{
    public:
        Grassland();
        Grassland(int);
        
        void roomSystem(Object*);
};

class Cabin : public Environment
{
    public:
        Cabin();
        Cabin(int);
        void roomSystem(Object*);
};


#endif  // ENVIRONMENT_H_INCLUDED