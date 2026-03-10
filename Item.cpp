#include "Item.h"
#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
using namespace std;

Item::Item() : Object("", "Item"), health(0), attack(0), defense(0) {}
Item::Item(string n, string tag, int hp, int a, int d, int h, int t) : Object(n, tag), health(hp), attack(a), defense(d), hunger(h), thirst(t) {}

bool Item::triggerEvent(Object *o)
{
    // cout << "Item" << endl;//test
    Player *p = dynamic_cast<Player *>(o);
    if (getTag() == "milk" || getTag() == "food" || getTag() == "drink" || getTag() == "others")
    {
        cout << "你用了" << getName() << endl;
        if (getHealth() != 0)
        {
            p->setCurrentHealth(getHealth());
        }
        if (getHunger() != 0)
        {
            p->setHunger(getHunger());
        }
        if (getThirst() != 0)
        {
            p->setThirst(getThirst());
        }
        if (getTag() == "milk" && p->getPoison() != nullptr)
        {
            p->setPoison(nullptr);
            cout << "你喝了奶，成功解毒了！" << endl;
        }
        return true;
    }
    else if (getTag() == "weapon" || getTag() == "potion")
    {
        // Weapon *f = dynamic_cast<Weapon *>(this);
        // f->triggerEvent(p);
        cout << "你用了" << getName() << endl;

        if (getAttack() != 0)
        {
            p->setAttackMax(p->getAttackMax() + getAttack());
            p->setAttackMin(p->getAttackMin() + getAttack());
        }
        if (getDefense() != 0)
        {
            p->setDefenseMax(p->getDefenseMax() + getDefense());
            p->setDefenseMin(p->getDefenseMin() + getDefense());
        }
        return true;
    }
    cout << "出現了一個神奇東東，你要撿嗎？" << endl; // 水、牛奶、肉
    cout << "1.撿" << endl;
    cout << "2.不撿" << endl;
    int choice;
    cin >> choice;
    srand(time(NULL));
    if (choice == 1)
    { // 改，有的直接用，有的放背包
        int random = rand() % 4;
        cout << random << endl; // test
        if (random == 0)
        {
            *this = foodAndDrink("肉", "food", 0, 20, 0);
        }
        else if (random == 1)
        {
            *this = foodAndDrink("水", "drink", 0, 0, 20);
        }
        else if (random == 2)
        {
            *this = foodAndDrink("牛奶", "milk", 0, 0, 20);
        }
        else
        {
            *this = foodAndDrink("補血藥水", "others", 20, 0, 0);
        }
        cout << "你撿起了神奇的東東，是" << getName() << "，要馬上用嗎" << endl;
        cout << "1.馬上用" << endl;
        cout << "2.先放背包" << endl;
        int choice2;
        cin >> choice2;
        if (choice2 == 1)
        {
            if (getHealth() != 0)
            {
                p->setCurrentHealth(getHealth());
            }
            if (getHunger() != 0)
            {
                p->setHunger(getHunger());
            }
            if (getThirst() != 0)
            {
                p->setThirst(getThirst());
            }
            cout << getName() << "已經被你用了" << endl;
        }
        else
        {
            if (getTag() == "food" || getTag() == "drink" || getTag() == "others" || getTag() == "milk")
            {
                p->addItem(*this);
            }
            else if (getTag() == "weapon" || getTag() == "potion")
            {
                p->addItem(*this);
            }
            cout << getName() << "已經被你放進背包了" << endl;
        }
        return true;
    }
    else
    {
        cout << "神奇的東東QQ" << endl;
        return false;
    }
}

int Item::getHealth()
{
    return health;
}
int Item::getAttack()
{
    return attack;
}
int Item::getDefense()
{
    return defense;
}
int Item::getHunger()
{
    return hunger;
}
int Item::getThirst()
{
    return thirst;
}
void Item::setHealth(int h)
{
    health = h;
}
void Item::setAttack(int a)
{
    attack = a;
}
void Item::setDefense(int d)
{
    defense = d;
}
void Item::setHunger(int h)
{
    hunger = h;
}
void Item::setThirst(int t)
{
    thirst = t;
}
Item *chest::getItem()
{
    return item;
}
void chest::setItem(Item *i)
{
    item = i;
}

chest::chest() : Item(nullptr, nullptr, 0, 0, 0, 0, 0), item(NULL) {}
chest::chest(string n) : Item(n, "chest", 0, 0, 0, 0, 0), item(NULL) {}
bool chest::triggerEvent(Object *o)
{
    Player *p = dynamic_cast<Player *>(o);
    cout << "這裡有一個寶箱，你要開嗎？" << endl;
    cout << "1.開" << endl;
    cout << "2.不開" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        getItem()->triggerEvent(p);
        return true;
    }
    else
    {
        cout << "寶箱QQ" << endl;
        return false;
    }
}

foodAndDrink water("水", "drink", 0, 0, 20);
foodAndDrink tissue("衛生紙", "others", 20, 0, 0); // 放哪
foodAndDrink mask("口罩", "others", 20, 0, 0);     // 放哪

foodAndDrink::foodAndDrink() : Item(nullptr, nullptr, 0, 0, 0, 0, 0) {}
foodAndDrink::foodAndDrink(string n, string tag, int hp, int h, int t) : Item(n, tag, hp, 0, 0, h, t) {}
bool foodAndDrink::triggerEvent(Object *o) // 改
{
    // cout << "Food" << endl;//test
    Player *p = dynamic_cast<Player *>(o);
    cout << "你拿到了一個" << getName() << "，要馬上";
    if (getTag() == "drink")
    {
        cout << "喝" << endl;
    }
    else if (getTag() == "food")
    {
        cout << "吃" << endl;
    }
    else
    {
        cout << "用" << endl;
    }
    cout << "嗎" << endl;
    cout << "1. 要" << endl;
    cout << "2. 放包包" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        if (getTag() == "drink")
        {
            cout << "你喝了" << getName() << "，你的口渴值增加了" << getThirst() << endl;
            p->setThirst(getThirst());
        }
        else if (getTag() == "food")
        {
            cout << "你吃了" << getName() << "，你的飢餓值增加了" << getHunger() << endl;
            p->setHunger(getHunger());
        }
        else
        {
            cout << "你用了" << getName() << "，你的血量增加了" << getHealth() << endl;
            p->setCurrentHealth(getHealth());
        }
        if (getTag() == "milk" && p->getPoison() != nullptr)
        {
            p->setPoison(nullptr);
            cout << "你喝了奶，成功解毒了！" << endl;
        }
        return true;
    }
    else
    {
        cout << "你把" << getName() << "放進背包" << endl;
        p->addItem(*this);
        return false;
    }
}

Poison::Poison() : Item(nullptr, "poison", 0, 0, 0, 0, 0), duration(0), antitode(0) {}
Poison::Poison(string n, int h, int d, string antitode) : Item(n, "poison", h, 0, 0, 0, 0), duration(d), lastDuration(d), antitode(antitode) {}
void Poison::setDuration(int d)
{
    duration = d;
}
void Poison::setAntitode(string a)
{
    antitode = a;
}
void Poison::setLastDuration()
{
    lastDuration = duration;
}
void Poison::setLastDuration(int d)
{
    lastDuration += d;
}
int Poison::getLastDuration()
{
    return lastDuration;
}
int Poison::getDuration()
{
    return duration;
}
string Poison::getAntitode()
{
    return antitode;
}
bool Poison::triggerEvent(Object *o)
{
    Player *p = dynamic_cast<Player *>(o);
    p->setPoison(this);
    cout << "你中了毒，每回合會扣" << getHealth() << "點血" << endl;
    cout << "毒效會持續" << getDuration() << "回合的時間" << endl;
    cout << getName() << "的解藥是" << getAntitode();
    vector<Item> inventory = p->getInventory();
    int a = 0;
    for (int i = 0; i < inventory.size(); i++)
    {
        if (inventory[i].getTag() == getAntitode())
        {
            a = 1;
            cout << "你的背包裡有，你要使用嗎" << endl;
            cout << "1. 要" << endl;
            cout << "2. 不要" << endl;
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                p->setPoison(nullptr);
                cout << "你成功解毒了" << endl;
                return true;
            }
            else
            {
                cout << "你繼續中毒" << endl;
                return true;
            }
            break;
        }
    }
    return true;
}

Weapon attackPotion("攻擊藥水", "potion", 10, 0);
Weapon defensePotion("防禦藥水", "potion", 0, 10);
Weapon::Weapon() : Item(nullptr, nullptr, 0, 0, 0, 0, 0) {}
Weapon::Weapon(string n, string tag, int a, int d) : Item(n, tag, 0, a, d, 0, 0) {}
bool Weapon::triggerEvent(Object *o) 
{
    // cout << "Weapon" << endl;//test
    Player *p = dynamic_cast<Player *>(o);
    cout << "你要用" << getName() << "嗎" << endl;
    cout << "1. 要" << endl;
    cout << "2. 放包包" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        cout << "你用了" << getName() << endl;
        if (getAttack() != 0)
        {
            p->setAttackMax(p->getAttackMax() + getAttack());
            p->setAttackMin(p->getAttackMin() + getAttack());
        }
        if (getDefense() != 0)
        {
            p->setDefenseMax(p->getDefenseMax() + getDefense());
            p->setDefenseMin(p->getDefenseMin() + getDefense());
        }
        return true;
    }
    else
    {
        cout << "你把" << getName() << "放進背包" << endl;
        p->addItem(*this);
        return false;
    }
}
