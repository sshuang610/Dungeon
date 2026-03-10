#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
using namespace std;

class Player;

class Item : public Object
{
private:
    int health;
    int attack;
    int defense;
    int hunger;
    int thirst;

public:
    Item();
    Item(string, string, int, int, int, int, int);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object *);

    /* Set & Get function*/
    int getHealth();
    int getAttack();
    int getDefense();
    int getHunger();
    int getThirst();
    void setHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setHunger(int);
    void setThirst(int);
;
};

class chest : public Item
{
private:
    Item *item;

public:
    chest();
    chest(string);
    bool triggerEvent(Object *);
    
    Item *getItem();
    void setItem(Item *);
    
};

class foodAndDrink : public Item
{
public:
    foodAndDrink();
    foodAndDrink(string, string, int, int, int);//name, tag, health, hunger, thirst
    bool triggerEvent(Object *);
};

class Poison : public Item
{
private:
    int duration;
    int lastDuration;
    string antitode;

public:
    Poison();
    Poison(string, int, int, string);//name, health, duration
    void setDuration(int);
    void setAntitode(string);
    void setLastDuration();
    void setLastDuration(int);
    int getLastDuration();
    int getDuration();
    string getAntitode();
    bool triggerEvent(Object *);
};

class Weapon : public Item
{
public:
    Weapon();
    Weapon(string, string, int, int);//name, attack, defense
    bool triggerEvent(Object *);
};

#endif // ITEM_H_INCLUDED