#ifndef GAMECHARACTER_H_INCLUDED
#define GAMECHARACTER_H_INCLUDED

#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

class GameCharacter: public Object
{
private:
    int maxHealth;
    int currentHealth;
    int attackMin;
    int attackMax;
    int defenseMin;
    int defenseMax;
public:
    GameCharacter();
    GameCharacter(string,string,int,int,int,int,int); 
    //1maxHealth, 2attackMin, 3attackMax, 4defenseMin, 5defenseMax
    bool checkIsDead();
    void takeDamage(int);

    /* Set & Get function*/
    void setMaxHealth(int);
    void setCurrentHealth(int);
    void setAttackMin(int);
    void setAttackMax(int);
    void setDefenseMin(int);
    void setDefenseMax(int);
    int getMaxHealth();
    int getCurrentHealth();
    int getAttackMin();
    int getAttackMax();
    int getDefenseMin();
    int getDefenseMax();
};
#endif // GAMECHARACTER_H_INCLUDED
