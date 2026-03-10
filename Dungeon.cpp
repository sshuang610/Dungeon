#include "Dungeon.h"
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
// #include "Record.h"
#include "Object.h"
#include "Environment.h"

using namespace std;

Dungeon::Dungeon() : player(), rooms() {}

void Dungeon::createPlayer()
{
    string name;
    cout << "請輸入你的名字: ";
    cin >> name;
    player.setName(name);
}

void Dungeon::createMap()
{
    for (int i = 0; i < 16; i++)
    {
        vector<Object *> objects;
        srand(time(NULL));
        Environment *e;
        // setting up the objects
        if (rand() % 2 == 0)
        {
            objects.push_back(new Item());
        }
        if (i == 2 || i == 5 || i == 7 || i == 8 || i == 10 || i == 13)
        {
            objects.push_back(new Monster("I love Dungeon"));
        }
        if (i == 3 || i == 9 || i == 11 || i == 12)
        {
            if (i == 3)
            {
                objects.push_back(new People("小熊"));
            }
            if (i == 9)
            {
                objects.push_back(new People("黃珊珊"));
            }
            if (i == 11)
            {
                objects.push_back(new People("Kelly"));
            }
            if (i == 12)
            {
                objects.push_back(new People("酒鬼"));
            }
        }
        if (i == 1 || i == 4 || i == 6 || i == 14) // Chest
        {
            if (i == 1)
            {
                chest *c = new chest("milk");
                c->setItem(new foodAndDrink("milk", "drink", 0, 0, 20));
                objects.push_back(c);
            }
            if (i == 4)
            {
                chest *c = new chest("iceCream");
                c->setItem(new foodAndDrink("iceCream", "food", 0, 30, 0));
                objects.push_back(c);
            }
            if (i == 6)
            {
                chest *c = new chest("sword");
                c->setItem(new Weapon("sword", "weapon", 10, 0));
                objects.push_back(c);
            }
            if (i == 14)
            {
                chest *c = new chest("sheild");
                c->setItem(new Weapon("sheild", "weapon", 0, 10));
                objects.push_back(c);
            }
        }
        if (i == 15)
        {
            objects.push_back(new Monster("Boss", 70, 30, 40, 10, 20));
        }
        // setting up the environment
        if (i == 0 || i == 5 || i == 7 || i == 10 || i == 13)
        {
            Grassland *g = new Grassland(i);
            e = g;
        }
        if (i == 1 || i == 4 || i == 11)
        {
            Desert *d = new Desert(i);
            e = d;
        }
        if (i == 2 || i == 8 || i == 15)
        {
            Forest *f = new Forest(i);
            e = f;
        }
        if (i == 3 || i == 12)
        {
            Cabin *c = new Cabin(i);
            e = c;
        }
        if (i == 6 || i == 9 || i == 14)
        {
            Swamp *s = new Swamp(i);
            e = s;
        }
        Room r(false, i, objects, e);
        if (i == 15)
            r.setIsExit(true);
        rooms.push_back(r);
    }
    for (int i = 0; i < 16; i++)
    {
        if (i + 4 < 16)
            rooms[i].setUpRoom(&rooms[i + 4]);
        if (i - 4 >= 0)
            rooms[i].setDownRoom(&rooms[i - 4]);
        if (i % 4 != 0)
            rooms[i].setLeftRoom(&rooms[i - 1]);
        if (i % 4 != 3)
            rooms[i].setRightRoom(&rooms[i + 1]);
    }
    cout << "Map created!" << endl;
}

void Dungeon::handleMovement()
{
    cout << "請輸入方向(w:上, s:下, a:左, d:右): " << endl;

    char direction;
    cin >> direction;

    switch (direction)
    {
    case 'w':
        if (player.getCurrentRoom()->getUpRoom() != NULL)
        {
            player.changeRoom(player.getCurrentRoom()->getUpRoom());
        }
        else
            cout << "無法前進" << endl;
        break;
    case 's':
        if (player.getCurrentRoom()->getDownRoom() != NULL)
            player.changeRoom(player.getCurrentRoom()->getDownRoom());
        else
            cout << "無法前進" << endl;
        break;
    case 'a':
        if (player.getCurrentRoom()->getLeftRoom() != NULL)
            player.changeRoom(player.getCurrentRoom()->getLeftRoom());
        else
            cout << "無法前進" << endl;
        break;
    case 'd':
        if (player.getCurrentRoom()->getRightRoom() != NULL)
            player.changeRoom(player.getCurrentRoom()->getRightRoom());
        else
            cout << "無法前進" << endl;
        break;
    default:
        cout << "輸入錯誤" << endl;
        break;
    }
} // 移動

bool Dungeon::handleEvent(Object *o)
{
    char ch;
    cin >> ch;
    switch (ch)
    {
    case 'C':
        player.triggerEvent(&player); // show status
        return false;
        break;
    case 'B':
        player.openBag(); // open bag, use item
        return false;
        break;
    case 'E':
        if (o->triggerEvent(&player))
        { // explore room
            player.getCurrentRoom()->removeObject(o);
        }
        return true;
        break;
    case 'M':
        handleMovement();
        break;
    default:
        return false;
        break;
    }
}

void Dungeon::startGame()
{
    cout << "歡迎來到遊戲！" << endl; // 介紹
    createPlayer();
    createMap();
    player.setCurrentRoom(&rooms[0]);
    // cout<< player.getCurrentRoom()->getIndex();
    cout << "遊戲開始!" << endl; // 開始

    return;
}

void Dungeon::chooseAction(vector<Object *> objects)
{
    for (int i = 0; i < objects.size();)
    {
        cout << "------------------------------------" << endl;
        checkHungerAndThirst();
        player.checkPoison();
        player.getCurrentRoom()->getEnvironment()->roomSystem(&player);
        checkGameLogic();
        cout << "------------------------------------" << endl;
        cout << "你想要做什麼呢?" << endl;
        cout << "(C)查看狀態" << endl;
        cout << "(B)打開背包" << endl;
        cout << "(E)探索房間" << endl;
        if (handleEvent(objects[i]))
        {
            i++;
        }
        if (!checkGameLogic())
        {
            return;
        }
    }
    cout << "------------------------------------" << endl;
    checkHungerAndThirst();
    player.checkPoison();
    player.getCurrentRoom()->getEnvironment()->roomSystem(&player);
    cout << "------------------------------------" << endl;
    cout << "現在是空的，想做什麼?" << endl;
    cout << "(C)查看狀態" << endl;
    cout << "(B)打開背包" << endl;
    cout << "(M)移動到下一個房間" << endl;
    handleEvent(NULL);
}

bool Dungeon::checkGameLogic()
{
    // check player's health and exist
    if (player.getCurrentHealth() <= 0)
    {
        cout << "You died!" << endl;
        exit(0);
    }
    if (player.getCurrentRoom()->getIsExit())
    {
        vector<Object *> objects = player.getCurrentRoom()->getObjects();
        for (int i = 0; i < objects.size(); i++)
        {
            if (dynamic_cast<Monster *>(objects[i]) != NULL)
            {
                return true;
            }
        }
        cout << "You win!" << endl;
        exit(0);
    }
    return true;
}

void Dungeon::checkHungerAndThirst()
{
    if (player.getHunger() == 0)
    {
        player.setCurrentHealth(-5);
        cout << "你超餓，所以被扣5滴血" << endl;
    }
    else
    {
        player.setHunger(-5);
    }
    if (player.getThirst() == 0)
    {
        player.setCurrentHealth(-5);
        cout << "你超渴，所以被扣5滴血" << endl;
        // debuff
        player.setAttackMax(player.getAttackMax() - 2);
        player.setAttackMin(player.getAttackMin() - 2);
        cout << "還有攻擊力也被減2點" << endl;
    }
    else
    {
        player.setThirst(-5);
    }
}

void Dungeon::runDungeon()
{
    startGame();

    while (checkGameLogic())
    {
        cout << endl
             << "------------------------------------" << endl;
        cout << "現在在Room " << player.getCurrentRoom()->getIndex();
        cout << " :Room的環境是" << player.getCurrentRoom()->getEnvironment()->getName() << endl;

        vector<Object *> objects = player.getCurrentRoom()->getObjects();
        chooseAction(objects);
    }
}