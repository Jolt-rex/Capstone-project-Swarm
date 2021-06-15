#include "Entity.h"

Entity::Entity(int id, int x, int y)
{
    _id = id;
    this->setLocation(x, y);
}

void Entity::setLocation(int x, int y)
{
    _x = x;
    _y = y;
}