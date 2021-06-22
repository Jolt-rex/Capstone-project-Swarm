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

// expand current node by adding all unvisited neighbours to open_list
// for each neighbour, set the parent, g_value and h_value
// set node to visited
void Enemy::AddNeighbours(std::shared_ptr<Node> currentNode)
{

}

// get the direct line distance of this object to the goal node
float Enemy::CalculateHValue()
{
    return std::sqrt(std::pow((this->_x - _goal->getX()), 2) + std::pow((this->_y - _goal->getY()), 2));
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