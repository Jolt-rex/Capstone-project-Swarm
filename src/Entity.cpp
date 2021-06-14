#include "Entity.h"

Entity::Entity(int id, int x, int y)
{
    this->setLocation(id, x, y);
}

void Entity::setLocation(int &id, int &x, int &y)
{
    _id = id;
    _x = x;
    _y = y;
}