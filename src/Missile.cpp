
#include <memory>
#include <iostream>
#include <thread>

#include "Missile.h"

Missile::Missile(int id, int x, int y, int speed) : Entity(id, x, y)
{
    _destroyed = false;
    _speed = speed;
    std::cout << "Missle #" << id << " created" << std::endl;
}

Missile::~Missile()
{
    std::cout << "Destroying missile #" << _id << std::endl;
}

void Missile::simulate()
{
    _threads.emplace_back(std::thread(&Missile::launch, this));
}

void Missile::launch()
{
    // while loop for missle movement // event handling
    while(!_destroyed)
    {
        // move towards target

    }
}

void Missile::destroy()
{
    _destroyed = true;
}

