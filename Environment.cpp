#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Environment.h"
#include "Player.h"
#include "Item.h"
#include "NPC.h"

using namespace std;

Wildlife tiger("老虎");
Wildlife wolf("狼");
Animal cow("牛牛");
Animal chicken("雞雞");
Animal sheep("羊羊");
Poison biogas("沼氣", 10, 3, "milk");


Environment::Environment() : roomIndex(), name() {}
Environment::Environment(int roomIndex, string s) : roomIndex(roomIndex), name(s) {}
int Environment::getRoomIndex()
{
    return roomIndex;
}
void Environment::setRoomIndex(int n)
{
    this->roomIndex = n;
}
string Environment::getName()
{
    return name;
}
void Environment::setName(string s)
{
    this->name = s;
}

Desert::Desert() : Environment() {}
Desert::Desert(int roomIndex) : Environment(roomIndex, "沙漠") {}
void Desert::setSandstormTime(int t)
{
    sandstormTime += t;
}
int Desert::getSandstormTime()
{
    return sandstormTime;
}
void Desert::roomSystem(Object *o)
{
    Player *p = dynamic_cast<Player *>(o);
    // thirst--
    if (getSandstormTime() > 0)
    {
        cout << "因沙塵暴，你的飢餓值和口渴值將額外下降10" << endl;
        p->setHunger(-10);
        p->setThirst(-10);
        setSandstormTime(-1);
        cout << "沙塵暴剩餘" << getSandstormTime() << "回合" << endl;
        return;
    }
    else
    {
        cout << "因為沙漠的炎熱，你的口渴值將額外下降5" << endl;
        p->setThirst(-5);
    }
    srand(time(0));
    int r1 = rand() % ((100 - 1) + 1) + 1;
    int r2 = rand() % ((100 - 1) + 1) + 1;
    if (r1 <= 30 && r1 >= 1)
    {
        // Sandstorm
        cout << "沙塵暴來襲，你的飢餓值和口渴值將額外連續下降10兩個回合" << endl;
        p->setHunger(-10);
        p->setThirst(-10);
        setSandstormTime(2);
        return;
    }
    if (r2 <= 10 && r2 >= 1)
    {
        // Oasis
        cout << "你遇到了一個綠洲，喝了一堆水，口渴值恢復回100" << endl;
        p->setThirst(100);
    }
}

Forest::Forest() : Environment() {}
Forest::Forest(int roomIndex) : Environment(roomIndex, "森林") {}
void Forest::roomSystem(Object *o)
{
    Player *p = dynamic_cast<Player *>(o);
    // hunger--
    cout << "你在森林中行走，飢餓值將額外下降5" << endl;
    p->setHunger(-5);
    srand(time(0));
    int r1 = rand() % ((100 - 1) + 1) + 1;
    int r2 = rand() % ((100 - 1) + 1) + 1;
    if (r1 <= 25 && r1 >= 1)
    {
        // wildlife
        int a = rand() % 2;
        if (a == 0)
        {
            cout << "老虎: 吼~\n";
            tiger.triggerEvent(p);
        }
        else
        {
            cout << "狼: 嗷~\n";
            wolf.triggerEvent(p);
        }
        return;
    }
    if (r2 <= 20 && r2 >= 1)
    {
        // Oasis
        cout << "你遇到了一個湖，喝了一些水，口渴值恢復50" << endl;
        p->setThirst(50);
    }
}

Swamp::Swamp() : Environment() {}
Swamp::Swamp(int roomIndex) : Environment(roomIndex, "沼澤") {}
void Swamp::roomSystem(Object *o)
{
    Player *p = dynamic_cast<Player *>(o);
    // hunger--, thirst--
    cout << "你在沼澤中行走，飢餓值和口渴值將額外下降5" << endl;
    p->setHunger(-5);
    p->setThirst(-5);
    srand(time(0));
    int r1 = rand() % ((100 - 1) + 1) + 1;
    int r2 = rand() % ((100 - 1) + 1) + 1;
    if (r1 <= 30 && r1 >= 1)
    {
        // poison
        cout << "你沼氣中毒了！" << endl;
        p->setPoison(&biogas);
        biogas.triggerEvent(p);
        return;
    }
    if (r2 <= 20 && r2 >= 1)
    {
        // 陷入沼澤，掉最後一個道具
        cout << "你不小心陷入沼澤了，雖然你用吃奶的力氣成功脫離了沼澤，但你遺失了一項道具" << endl;
        if ((p->getInventory()).size() > 0)
        {
            cout << "你遺失了" << p->getInventory().back().getName() << endl;
            p->removeItem(p->getInventory().size() - 1);
        }
        else
        {
            cout << "結果你連道具都沒有，笑你哈哈" << endl;
        }
    }
}

Grassland::Grassland() : Environment() {}
Grassland::Grassland(int roomIndex) : Environment(roomIndex, "草原") {}
void Grassland::roomSystem(Object *o)
{
    Player *p = dynamic_cast<Player *>(o);
    cout << "你走在草原上，沒有任何事發生" << endl;
    srand(time(0));
    int r1 = rand() % ((100 - 1) + 1) + 1;
    int r2 = rand() % ((100 - 1) + 1) + 1;
    if (r1 <= 40 && r1 >= 1)
    {
        // animal
        int a = rand() % 3;
        if (a == 0)
        {
            cout << "牛牛: 哞~\n";
            cow.triggerEvent(p);
        }
        else if (a == 1)
        {
            cout << "雞雞: 咕咕咕~\n";
            chicken.triggerEvent(p);
        }
        else
        {
            cout << "羊羊: 咩~\n";
            sheep.triggerEvent(p);
        }
        return;
    }
    if (r2 <= 30 && r2 >= 1)
    {
        // 吃草
        cout << "你覺得地上的草看起來很好吃，所以你就吃了一把，你覺得自己變得更健康了" << endl;
        p->setCurrentHealth(30);
    }
}

Cabin::Cabin() : Environment() {}
Cabin::Cabin(int roomIndex) : Environment(roomIndex, "林間小屋") {}
void Cabin::roomSystem(Object *o)
{
    Player *p = dynamic_cast<Player *>(o);
    cout << "現在位於林間小屋，你在這裡補充了能量，飢餓值和口渴值上升了10%" << endl;
    p->setHunger(10);
    p->setThirst(10);
    srand(time(0));
    int r1 = rand() % ((100 - 1) + 1) + 1;
    int r2 = rand() % ((100 - 1) + 1) + 1;
    if (r1 <= 40 && r1 >= 1)
    {
        // sleep
        cout << "你在小屋裡睡了一下，生命值恢復了50" << endl;
        p->setCurrentHealth(50);
        return;
    }
    if (r2 <= 10 && r2 >= 1)
    {
        // 怪湯
        cout << "桌上有一晚怪怪的湯，你要喝嗎" << endl;
        cout << "1. 喝" << endl;
        cout << "2. 不喝" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            cout << "你喝了一口，覺得很好喝，所有狀態數值都恢復了" << endl;
            p->setCurrentHealth(100);
            p->setHunger(100);
            p->setThirst(100);
            p->setPoison(NULL);
        }
        else
        {
            cout << "你決定不喝" << endl;
        }
    }
}
