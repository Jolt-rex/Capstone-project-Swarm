
#include <memory>
#include <iostream>
#include <thread>

#include "Missile.h"

Missile::Missile(int id, int x, int y) : Entity(id, x, y)
{
    _isFlying = true;
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
    
}

