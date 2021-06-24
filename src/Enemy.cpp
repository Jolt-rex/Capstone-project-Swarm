#include <iostream>
#include <vector>
#include <memory>
#include <math.h>
#include "Enemy.h"
#include "Model.h"

// create enemy, using the path vector to create at start position
Enemy::Enemy(int id, int speed, std::vector<std::shared_ptr<Node>> path) : 
    Entity(id, path.front()->getX(), path.front()->getY())
{
    std::cout << "Constructing enemy.. " << std::endl;

    _route = path;

    std::cout << "Enemy path:\n";
    for(const auto &node : _route) {
        std::cout << "Id:" << node->getId() << " x:" << node->getX() << " y:" << node->getY() << std::endl; 
    }

    _speed = speed;
}
