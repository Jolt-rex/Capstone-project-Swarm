#include "Entity.h"

#include <iostream>
#include <algorithm>
#include <thread>

// Base class for Node, Enemy, Tower and Missile
Entity::Entity(int id, double x, double y)
{
    _id = id;
    this->setLocation(x, y);
}

Entity::~Entity()
{
    // std::cout << "Destroying entity : " << _id << std::endl;
    // ensure all threads held by this object are joined
    //std::for_each(_threads.begin(), _threads.end(), [](std::thread &t) { t.join(); });
}

void Entity::setLocation(double x, double y)
{
    _x = x;
    _y = y;
}

const double Entity::getX()
{
    std::unique_lock<std::mutex> u_lock(_mutex);
    return _x;
}

const double Entity::getY() 
{ 
    std::unique_lock<std::mutex> u_lock(_mutex);
    return _y; 
}