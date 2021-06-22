#include <iostream>
#include "math.h"
#include "Entity.h"
#include "Node.h"

// call parent constructor with values id, x and y position
Node::Node(int id, double x, double y, bool isGoal, bool isSpawnPoint) : Entity(id, x, y) 
{
    //std::cout << "Creating Node" << std::endl;

    _goal = isGoal;
    _spawnPoint = isSpawnPoint;
}

void Node::AddConnected(std::shared_ptr<Node> node)
{
    _connectedNodes.push_back(node);
}

std::vector<std::shared_ptr<Node>> Node::GetConnected() const
{
    return _connectedNodes;
}

double Node::Distance(std::shared_ptr<Node> node)
{
    return std::sqrt(std::pow((_x - node->getX()), 2) + std::pow((_y - node->getY()), 2));
}

