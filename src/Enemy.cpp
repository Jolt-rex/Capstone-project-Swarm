#include <iostream>
#include <vector>
#include <memory>
#include <math.h>
#include "Enemy.h"
#include "Model.h"

// create enemy, using the path vector to create at start position
Enemy::Enemy(int id, int speed, std::vector<std::shared_ptr<Node>> _path) : 
    Entity(id, _path.front()->getX(), _path.front()->getY())
{
    std::cout << "Constructing enemy.. " << std::endl;

    _speed = speed;

}
