#include "Entity.h"

Entity::Entity(int id, float x, float y)
{
    _id = id;
    this->setLocation(x, y);
}

void Entity::setLocation(float x, float y)
{
    _x = x;
    _y = y;
}