#include "Object.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Object::Object()
{
    name = "";
    tag = "";
}
Object::Object(string name, string tag) : name(name), tag(tag) {}

bool Object::triggerEvent(Object* o){return false;}

void Object::setName(string name)
{
    this->name = name;
}
void Object::setTag(string tag)
{
    this->tag = tag;
}
string Object::getName()
{
    return name;
}
string Object::getTag()
{
    return tag;
}

