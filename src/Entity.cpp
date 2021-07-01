#include "Entity.h"

#include <iostream>
#include <algorithm>
#include <thread>

Entity::Entity(int id, double x, double y)
{
    _id = id;
    this->setLocation(x, y);
}

Entity::~Entity()
{
    std::cout << "Destroying entity : " << _id << std::endl;
}

void Entity::setLocation(double x, double y)
{
    _x = x;
    _y = y;
}