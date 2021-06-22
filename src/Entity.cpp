#include "Entity.h"

Entity::Entity(int id, double x, double y)
{
    _id = id;
    this->setLocation(x, y);
}

void Entity::setLocation(double x, double y)
{
    _x = x;
    _y = y;
}