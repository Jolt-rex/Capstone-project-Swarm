#include <iostream>
#include <math.h>
#include "Enemy.h"

Enemy::Enemy(int id, double x, double y) : Entity(id, x, y)
{
    std::cout << "Constructing enemy.. " << std::endl;
}
