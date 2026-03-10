#include "GameCharacter.h"
#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

GameCharacter::GameCharacter() : Object("", "GameCharacter"), maxHealth(0), currentHealth(0), attackMin(0), attackMax(0), defenseMin(0), defenseMax(0) {}

GameCharacter::GameCharacter(string n, string tag, int mh, int aMin, int aMax, int dMin, int dMax) : Object(n, tag), maxHealth(mh), currentHealth(mh), attackMin(aMin), attackMax(aMax), defenseMin(dMin), defenseMax(dMax) {}

bool GameCharacter::checkIsDead()
{
    if (currentHealth <= 0)
    {
        return true;
    }
    return false;
}

void GameCharacter::takeDamage(int damage)
{
    currentHealth -= damage;
}

void GameCharacter::setMaxHealth(int mh)
{
    maxHealth = mh;
}
void GameCharacter::setCurrentHealth(int ch)
{
    if (ch == maxHealth)
    {
        currentHealth = maxHealth;
        cout << "生命值: " << getCurrentHealth() << "/" << getMaxHealth() << endl;
        return;
    }
    cout << "生命值: " << getCurrentHealth();
    if (ch > 0)
    {
        cout << "+" << ch;
    }
    else
    {
        cout << ch;
    }
    cout << "->";
    if (currentHealth + ch > maxHealth)
    {
        currentHealth = maxHealth;
    }
    else if (currentHealth + ch <= 0)
    {
        currentHealth = 0;
    }
    else
    {
        currentHealth += ch;
    }
    cout << currentHealth << "/" << getMaxHealth() << endl;
}
void GameCharacter::setAttackMin(int a)
{
    attackMin = a;
}
void GameCharacter::setAttackMax(int a)
{
    int n = a - attackMax;
    attackMax = a;
    cout << "攻擊力增加" << n;
}
void GameCharacter::setDefenseMin(int d)
{
    defenseMin = d;
}
void GameCharacter::setDefenseMax(int d)
{
    int n = d - defenseMax;
    defenseMax = d;
    cout << "防禦力增加" << n;
}
int GameCharacter::getMaxHealth()
{
    return maxHealth;
}
int GameCharacter::getCurrentHealth()
{
    return currentHealth;
}
int GameCharacter::getAttackMin()
{
    return attackMin;
}
int GameCharacter::getAttackMax()
{
    return attackMax;
}
int GameCharacter::getDefenseMin()
{
    return defenseMin;
}
int GameCharacter::getDefenseMax()
{
    return defenseMax;
}