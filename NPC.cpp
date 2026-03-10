#include "NPC.h"
#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;

NPC::NPC() : GameCharacter() {}
NPC::NPC(string n) : GameCharacter(n, "NPC", 0, 0, 0, 0, 0){}
bool NPC::triggerEvent(Object *o)
{
    cout << "你遇到了" << getName() << endl;
    // 跟NPC的互動
    return true;
}


People::People() : NPC() {}
People::People(string n) : NPC(n) {}
bool People::triggerEvent(Object *o)
{
    Player *p = dynamic_cast<Player *>(o);
    cout << "你遇到了" << getName()  << endl;
    // 跟People的互動
    if (getName() == "小熊")
    {
        cout << "小熊: 一隻小熊在跳舞，呼啦呼啦啦\n小熊: 哈囉~ 我是小熊，我這邊有一瓶攻擊藥水和一瓶防禦藥水，你想要拿你的一項東西跟我換嗎?\n小熊: 或是你要跟我換一個愛的抱抱也可以(´∀`) " << endl;
        cout << "小熊: 你要跟我換什麼呢?" << endl;
        cout << "1.攻擊藥水" << endl;
        cout << "2.防禦藥水" << endl;
        cout << "3.愛的親親" << endl;
        cout << "4.我不想換" << endl;
        int choice;
        cin >> choice;
        if (choice == 4)
        {
            cout << "小熊: 那好吧，掰掰囉!" << endl;
            return false;
        }
        else
        {
            if (p->getInventory().size() == 0)
            {
                cout << "小熊: 哇勒，但你的背包是空的ㄟ，那你下次再來吧，掰掰!" << endl;
                return false;
            }
            cout << "小熊: 那你要用什麼跟我換呢?" << endl;
            for (int i = 0; i < p->getInventory().size(); i++)
            {
                cout << i + 1 << "." << p->getInventory()[i].getName() << endl;
            }
            int choice2;
            cin >> choice2;
            p->removeItem(choice2-1);
            cout << "小熊: 好喔，給你";
            if (choice == 1)
            {
                cout << "攻擊藥水！" << endl;
                p->addItem(Weapon("attackPotion", "weapon", 15, 0));
            }
            else if (choice == 2)
            {
                cout << "防禦藥水！" << endl;
                p->addItem(Weapon("defensePotion", "weapon", 0, 15));
            }
            else if (choice == 3)
            {
                cout << "愛的親親！" << endl;
                cout << "小熊: mua♡♡" << endl;
                cout << "小熊: 我最喜歡親親了，這是我最珍貴的東西，你要好好珍惜喔(´∀`)" << endl;
                p->setCurrentHealth(100);
                p->setHunger(100);
                p->setThirst(100);
            }
            cout << "小熊: 掰掰囉!(^3^)" << endl;
            return true;
        }
    }
    else if (getName() == "黃珊珊")
    {
        cout << "黃珊珊: 您好，我是台北市市長候選人8號黃珊珊\n黃珊珊: 只要您答應11/26投珊珊一票，就可以拿到免費的競選小物喔!" << endl;
        cout << "11/26市長大選，你會投黃珊珊一票嗎?" << endl;
        cout << "1. 那必須的" << endl;
        cout << "2. 不要" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            cout << "黃珊珊: 謝謝您的支持，那你要哪個競選小物呢?" << endl;
            cout << "1.衛生紙" << endl;
            cout << "2.水" << endl;
            cout << "3.口罩" << endl;
            int choice2;
            cin >> choice2;
            cout << "黃姍姍: 這給您，請收下!" << endl;
            if (choice2 == 1)
            {
                p->addItem(foodAndDrink("衛生紙", "others", 20, 0, 0));
            }
            else if (choice2 == 2)
            {
                p->addItem(foodAndDrink("水", "drink", 0, 0, 20));
            }
            else if (choice2 == 3)
            {
                p->addItem(foodAndDrink("口罩", "others", 20, 0, 0));
            }
            cout << "黃珊珊: 請記得11/26投黃珊珊一票，姍姍感謝您!" << endl;
            return true;
        }
        else
        {
            cout << "黃珊珊: 好吧，謝謝您的時間，掰掰!" << endl;
            return false;
        }
    }
    else if (getName() == "Kelly")
    {
        cout << "Kelly: ㄟ我剛剛去清夜買了一些消夜，你要吃嗎?\nKelly: 我這邊有開源社、立晉、來來，拿一東西跟我換就給你吃!" << endl;
        cout << "Kelly: 你要吃什麼呢?" << endl;
        cout << "1.開源社" << endl;
        cout << "2.立晉" << endl;
        cout << "3.來來" << endl;
        cout << "4.我在減肥" << endl;
        int choice;
        cin >> choice;
        if (choice == 4)
        {
            cout << "Kelly: 好吧，掰掰!" << endl;
            return false;
        }
        else
        {
            if (p->getInventory().size() == 0)
            {
                cout << "Kelli: 痾但你的背包是空的ㄟ，那你下次再來吧，掰!" << endl;
                return false;
            }
            cout << "Kelly: 那你要用什麼換呢?" << endl;
            for (int i = 0; i < p->getInventory().size(); i++)
            {
                cout << i + 1 << "." << p->getInventory()[i].getName() << endl;
            }
            int choice2;
            cin >> choice2;
            p->removeItem(choice2-1);
            cout << "Kelly: 來，這給你吃吧!" << endl;
            if (choice == 1)
            {
                p->addItem(foodAndDrink("開源社", "food", 0, 30, 0));
            }
            else if (choice == 2)
            {
                p->addItem(foodAndDrink("立晉", "drink", 0, 0, 20));
            }
            else if (choice == 3)
            {
                p->addItem(foodAndDrink("來來", "food", 0, 20, 0));
            }
            cout << "Kelly: 掰掰!" << endl;
            return true;
        }
    }
    else if (getName() == "酒鬼")
    {
        cout << "酒鬼: 喝喝喝呵呵\n酒鬼: 我最愛喝酒了呵呵\n酒鬼: 你要喝嗎呵呵\n酒鬼: 拿一個東西跟我換就給你喝一杯呵呵" << endl;
        cout << "酒鬼: 你要喝什麼呢呵呵" << endl;
        cout << "1.啤酒" << endl;
        cout << "2.伏特加" << endl;
        cout << "3.生命之水" << endl;
        cout << "4.我戒酒了" << endl;
        int choice;
        cin >> choice;
        if (choice == 4)
        {
            cout << "酒鬼: 好吧，掰掰呵呵" << endl;
            return false;
        }
        else
        {
            if (p->getInventory().size() == 0)
            {
                cout << "酒鬼: 修但幾咧，你的背包沒東西ㄟ，那你下次再來跟我喝吧，掰掰呵呵" << endl;
                return false;
            }
            cout << "酒鬼: 那你要用什麼跟我換呢呵呵" << endl;
            for (int i = 0; i < p->getInventory().size(); i++)
            {
                cout << i + 1 << "." << p->getInventory()[i].getName() << endl;
            }
            int choice2;
            cin >> choice2;
            p->removeItem(choice2-1);
            cout << "酒鬼: 一起喝喝呵呵!" << endl;
            // push item to player's inventory, pop item from NPC's commodity, 顯示文字
            if (choice == 1)
            {
                p->setPoison(new Poison("啤酒", 5, 2, "milk"));
            }
            else if (choice == 2)
            {
                p->setPoison(new Poison("伏特加", 5, 3, "milk"));
            }
            else if (choice == 3)
            {
                p->setPoison(new Poison("生命之水", 10, 2, "milk"));
            }
            cout << "你喝了" << p->getPoison()->getName() << "，你酒精中毒了！" << endl;
            p->getPoison()->triggerEvent(p);
            cout << "酒鬼: 掰掰呵呵呵" << endl;
            return true;
        }
    }
    return true;
}

Wildlife::Wildlife() : NPC() {}
Wildlife::Wildlife(string n) : NPC(n) {}
bool Wildlife::triggerEvent(Object *o)
{
    Player *p = dynamic_cast<Player *>(o);
    cout << "你遇到了" << getName() << endl;
    // 跟Wildlife的互動
    cout << getName() << ": 我現在很餓，我想要吃肉，如果你給我一塊肉的話，我就會放過你" << endl;
    for (int i = 0; i < p->getInventory().size(); i++)
    {
        cout << "ha" << endl;//test
        if (p->getInventory()[i].getName() == "肉")
        {
            cout << "你的背包裡有肉，你要給" << getName() << "一塊肉嗎?" << endl;
            cout << "1. 要" << endl;
            cout << "2. 不要" << endl;
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                p->removeItem(i);
                cout << "你給了" << getName() << "一塊肉，你成功活下來了" << endl;
                return true;
            }
            else
            {
                cout << "不給是吧，那我要吃掉你身上的一塊肉" << endl;
                p->setCurrentHealth(-40);
                // 台詞
                return true;
            }
        }
    }
    cout << "你沒有肉，" << getName() << "吃掉了你身上的一塊肉" << endl;
    p->setCurrentHealth(-40);
    return true;
}

Animal::Animal() : NPC() {}
Animal::Animal(string n) : NPC(n) {}
bool Animal::triggerEvent(Object *o)
{
    Player *p = dynamic_cast<Player *>(o);
    cout << "你遇到了" << getName() << endl;
    // 跟Animal的互動
    cout << "你要對" << getName() << "做什麼呢?" << endl;
    cout << "1. 吃牠" << endl;
    cout << "2. ";
    if (getName() == "牛牛")
    {
        cout << "獲取牛奶" << endl;
    }
    else if (getName() == "雞雞")
    {
        cout << "偷雞蛋" << endl;
    }
    else if (getName() == "羊羊")
    {
        cout << "獲取羊奶" << endl;
    }
    cout << "3. 不理牠" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) // 台詞
    {
        cout << "你怎麼忍心殺了可愛的" << getName() << "！\n沒想到你這麼殘忍...\n但你還是成功獲得了" << getName() << "的肉" << endl;
        p->addItem(foodAndDrink("肉", "food", 0, 20, 0));
        return true;
    }
    else if (choice == 2 && getName() == "雞雞")
    {
        cout << "你得到了" << getName() << "的蛋蛋\n" << endl;
        p->addItem(foodAndDrink("蛋蛋", "milk", 0, 20, 0));
        return true;
    }
    else if (choice ==2 && getName() == "牛牛"){
        cout << "你得到了" << getName() << "的奶\n(偷偷告訴你，它可以用來解毒喔~)" << endl;
        p->addItem(foodAndDrink("牛奶", "milk", 0, 0, 20));
        return true;
    }
    else if (choice ==2 && getName() == "羊羊"){
        cout << "你得到了" << getName() << "的奶\n(偷偷告訴你，它可以用來解毒喔~)" << endl;
        p->addItem(foodAndDrink("羊奶", "milk", 0, 0, 20));
        return true;
    }
    else
    {
        cout << "你頭也不回的離開了" << getName() << "，" << getName() << "QQ" << endl;
        return false;
    }
}
