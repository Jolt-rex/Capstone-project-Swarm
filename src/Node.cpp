#include <iostream>
#include "Entity.h"
#include "Node.h"

// call parent constructor with values id, x and y position
Node::Node(int id, int x, int y, bool isGoal, bool isSpawnPoint) : Entity(id, x, y) 
{
    //std::cout << "Creating Node" << std::endl;

    _goal = isGoal;
    _spawnPoint = isSpawnPoint;
}

void Node::addPath(std::shared_ptr<Path> path)
{
    _paths.push_back(path);
}
