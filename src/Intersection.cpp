#include <iostream>
#include "Entity.h"
#include "Intersection.h"

// call parent constructor with values id, x and y position
Intersection::Intersection(int id, int x, int y, bool isGoal, bool isSpawnPoint) : Entity(id, x, y) 
{
    std::cout << "Creating intersection" << std::endl;

    _goal = isGoal;
    _spawnPoint = isSpawnPoint;
}

void Intersection::addPath(std::shared_ptr<Path> path)
{
    _paths.push_back(path);
}
