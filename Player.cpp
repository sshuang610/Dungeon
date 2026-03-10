#include "Player.h"
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;

Player::Player() : GameCharacter("", "Player", 200, 25, 35, 10, 30), hunger(100), thirst(100), poison(NULL), currentRoom(NULL), previousRoom(NULL), inventory() {}
Player::Player(string n) : GameCharacter(n, "Player", 200, 25, 35, 10, 30), hunger(100), thirst(100), poison(NULL), currentRoom(NULL), previousRoom(NULL), inventory() {}
void Player::addItem(Item i)
{
    inventory.push_back(i);
    cout << "已將" << i.getName() << "放入背包" << endl;
}
void Player::removeItem(int i)
{
    cout << "已將" << inventory[i].getName() << "從背包中移除" << endl;
    inventory.erase(inventory.begin() + i);
}
void Player::increaseStates(int h, int a, int d)
{
    setCurrentHealth(getCurrentHealth() + h);
    setAttackMin(getAttackMin() + a);
    setAttackMax(getAttackMax() + a);
    setDefenseMin(getDefenseMin() + d);
    setDefenseMax(getDefenseMax() + d);
}
void Player::changeRoom(Room *r)
{
    previousRoom = currentRoom;
    currentRoom = r;
}
bool Player::checkPoison()
{
    if (poison != nullptr)
    {
        cout << "因為中毒所以被扣了" << poison->getHealth() << " 滴血!" << endl;
        setCurrentHealth(getCurrentHealth() - poison->getHealth());
        poison->setLastDuration(-1);
        if (poison->getLastDuration() == 0)
        {
            cout << "毒效沒了!" << endl;
            poison->setLastDuration();
            poison = nullptr;
        }
        return true;
    }
    return false;
}

bool Player::triggerEvent(Object *o)
{
    cout << "Player: " << getName() << endl;
    cout << "Health: " << getCurrentHealth() << "/" << getMaxHealth() << endl;
    cout << "Attack: " << getAttackMin() << "~" << getAttackMax() << endl;
    cout << "Defense: " << getDefenseMin() << "~" << getDefenseMax() << endl;
    cout << "Hunger: " << hunger << endl;
    cout << "Thirst: " << thirst << endl;
    cout << "Poison: ";
    if (poison == nullptr)
    {
        cout << "no" << endl;
    }
    else
    {
        cout << poison->getName() << endl;
    }
    return true;
}
void Player::openBag()
{
    if (inventory.size() == 0)
    {
        cout << "你的背包是空的" << endl;
        return;
    }
    cout << "背包: ";
    for (int i = 0; i < inventory.size(); i++)
    {
        cout << i + 1 << ". " << inventory[i].getName() << " ";
    }
    cout << "你要做什麼" << endl;
    cout << "1. 使用物品" << endl;
    cout << "2. 返回動作選單" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        cout << "你要使用哪個物品?" << endl;
        for (int i = 0; i < inventory.size(); i++)
        {
            cout << i + 1 << ". " << inventory[i].getName() << " ";
        }
        int itemChoice;
        cin >> itemChoice;
        inventory[itemChoice - 1].triggerEvent(this);
        inventory.erase(inventory.begin() + itemChoice - 1);
    }
    else if (choice == 2)
    {
        return;
    }
}

void Player::setHunger(int h)
{
    if (h == 100)
    {
        hunger = 100;
        cout << "飢餓值: " << getHunger() << "->100" << endl;
        return;
    }
    cout << "飢餓值: " << getHunger();
    if (h > 0)
    {
        cout << "+" << h;
    }
    else
    {
        cout << h;
    }
    cout << "->";
    if (getHunger() + h < 0)
    {
        cout << "0" << endl;
        hunger = 0;
        return;
    }
    else if (getHunger() + h > 100)
    {
        cout << "100" << endl;
        hunger = 100;
        return;
    }
    cout << getHunger() + h << endl;
    hunger += h;
}
void Player::setThirst(int t)
{
    if (t == 100)
    {
        thirst = 100;
        cout << "口渴值: " << getThirst() << "->100" << endl;
        return;
    }
    cout << "口渴值: " << getThirst();
    if (t > 0)
    {
        cout << "+" << t;
    }
    else
    {
        cout << t;
    }
    cout << "->";
    if (getThirst() + t < 0)
    {
        cout << "0" << endl;
        thirst = 0;
        return;
    }
    else if (getThirst() + t > 100)
    {
        cout << "100" << endl;
        thirst = 100;
        return;
    }
    cout << getThirst() + t << endl;
    thirst += t;
}
void Player::setPoison(Poison *p)
{
    poison = p;
}
void Player::setCurrentRoom(Room *r)
{
    currentRoom = r;
}
void Player::setPreviousRoom(Room *r)
{
    previousRoom = r;
}
void Player::setInventory(vector<Item> i)
{
    //?
}
Room *Player::getCurrentRoom()
{
    return currentRoom;
}
Room *Player::getPreviousRoom()
{
    return previousRoom;
}
vector<Item> Player::getInventory()
{
    return inventory;
}
int Player::getHunger()
{
    return hunger;
}
int Player::getThirst()
{
    return thirst;
}
Poison *Player::getPoison()
{
    return poison;
}