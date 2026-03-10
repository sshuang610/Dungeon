#include "Monster.h"
#include "GameCharacter.h"
#include "Player.h"


Monster::Monster(): GameCharacter(){}

Monster::Monster(string n): GameCharacter(n, "Monster", 50, 20, 40, 5, 15){}

Monster::Monster(string n, int mh, int aMin, int aMax, int dMin, int dMax): GameCharacter(n, "Monster", mh, aMin, aMax, dMin, dMax){}

bool Monster::triggerEvent(Object * o){
    Player * p = dynamic_cast<Player *>(o);
    cout << "你遇到Monster了！" << endl;
    cout << "Monster的名字: " << getName() << endl;
    while(p->getCurrentHealth() > 0 && getCurrentHealth() > 0){//(加入攻擊機制
    cout << "Monster的血量: " << getCurrentHealth() <<"/"<<getMaxHealth()<< endl;
    cout << "你要攻擊還是逃跑？" << endl;
    cout << "1. 攻擊" << endl;
    cout << "2. 逃跑(返回上個房間)" << endl;
    int choice;
    cin >> choice;//調整攻擊機制
    if(choice == 1){
        srand(time(NULL));
        int damage = (rand() % (p->getAttackMax() - p->getAttackMin() + 1) + p->getAttackMin())-(rand() % (getDefenseMax() - getDefenseMin() + 1) + getDefenseMin());
        if(damage < 0){
            damage = 0;
        }
        cout << "你對" << getName() << "造成了" << damage << "點的傷害!" << endl;
        takeDamage(damage);
        if(getCurrentHealth() <= 0){
            cout << "你成功打敗"<< getName() << "!" << endl;
            return true;
        }
        else{
            damage = (rand() % (getAttackMax() - getAttackMin() + 1) + getAttackMin())-(rand() % (p->getDefenseMax() - p->getDefenseMin() + 1) + p->getDefenseMin());
            if(damage < 0){
                damage = 0;
            }
            cout << getName() << "對你造成了" << damage << "點的傷害!" << endl;
            p->takeDamage(damage);
            cout<< "你的血量: " << p->getCurrentHealth() << "/" << p->getMaxHealth() << endl;
            p->checkIsDead();
        }
    }
    else if(choice == 2){
        cout << "你回到了上一個房間" << endl;
        p->changeRoom(p->getPreviousRoom());
        return false;
    }
    else{
        cout << "沒有這個選項!" << endl;
    }
    }
    return true;
}