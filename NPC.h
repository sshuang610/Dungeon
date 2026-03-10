#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;

class NPC: public GameCharacter
{
public:
    NPC();
    NPC(string);
    bool triggerEvent(Object*);
};

class People : public NPC
{
public:
    People();
    People(string);
    bool triggerEvent(Object*);
};

class Wildlife : public NPC
{
public:
    Wildlife();
    Wildlife(string);
    bool triggerEvent(Object*);
};

class Animal : public NPC
{
public:
    Animal();
    Animal(string);
    bool triggerEvent(Object*);
};

#endif // NPC_H_INCLUDED
