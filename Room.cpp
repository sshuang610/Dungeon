#include "Room.h"
#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Environment.h"

using namespace std;

Room::Room(): upRoom(NULL), downRoom(NULL), leftRoom(NULL), rightRoom(NULL), isExit(false), index(0), objects(), environment(){}
Room::Room(bool ie, int i, vector<Object*> o, Environment *e): upRoom(NULL), downRoom(NULL), leftRoom(NULL), rightRoom(NULL), isExit(ie), index(i), objects(o), environment(e){}
void Room::removeObject(Object* o){
    for(int i = 0; i < objects.size(); i++){
        if(objects[i] == o){
            objects.erase(objects.begin() + i);
            return;
        }
    }
}


void Room::setUpRoom(Room* r){
    upRoom = r;
}
void Room::setDownRoom(Room* r){
    downRoom = r;
}
void Room::setLeftRoom(Room* r){
    leftRoom = r;
}
void Room::setRightRoom(Room* r){
    rightRoom = r;
}
void Room::setIsExit(bool ie){
    isExit = ie;
}
void Room::setIndex(int i){
    index = i;
}
void Room::setObjects(vector<Object*> o){
    objects = o;
}
Environment* Room::getEnvironment(){
    return environment;
}
bool Room::getIsExit(){
    return isExit;
}
int Room::getIndex(){
    return index;
}
vector<Object*> Room::getObjects(){
    return objects;
}
Room* Room::getUpRoom(){
    return upRoom;
}
Room* Room::getDownRoom(){
    return downRoom;
}
Room* Room::getLeftRoom(){
    return leftRoom;
}
Room* Room::getRightRoom(){
    return rightRoom;
}