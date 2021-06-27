#include "Entity.h"

#include <algorithm>
#include <thread>

Entity::Entity(int id, double x, double y)
{
    _id = id;
    this->setLocation(x, y);
}

// make sure all threads belonging to this object are joined / finised
Entity::~Entity()
{
    std::for_each(_threads.begin(), _threads.end(), [](std::thread &th) {
        th.join();
    });
}

void Entity::setLocation(double x, double y)
{
    _x = x;
    _y = y;
}