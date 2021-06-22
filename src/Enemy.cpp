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

std::shared_ptr<Node> Enemy::NextNode()
{

}

    // private:
    //     int _speed;
    //     float _distance = 0.0f;

    //     // route planning members
    //     std::shared_ptr<Node> _origin;
    //     std::shared_ptr<Node> _goal;
    //     std::vector<std::shared_ptr<Node>> _route;
    //     std::vector<std::shared_ptr<Node>> _open_list;

    //     // access to the model for calculating route
    //     std::shared_ptr<Model> _model;