#include <iostream>
#include <math.h>
#include "Enemy.h"

Enemy::Enemy(int id, float x, float y) : Entity(id, x, y)
{
    std::cout << "Constructing enemy.. " << std::endl;
}

void Enemy::ConstructPath()
{

}