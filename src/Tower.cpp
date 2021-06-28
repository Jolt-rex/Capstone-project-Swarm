#include <iostream>

#include "Entity.h"
#include "Tower.h"

Tower::Tower(int id, double x, double y) : Entity(id, x, y)
{
    std::cout << "Creating tower #" << id << std::endl;
}