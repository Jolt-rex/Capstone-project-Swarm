#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <math.h>
#include "Enemy.h"
#include "Model.h"

// create enemy, using the path vector to create at start position
Enemy::Enemy(int id, int speed, std::vector<std::shared_ptr<Node>> path) : 
    Entity(id, path.front()->getX(), path.front()->getY())
{
    std::cout << "Constructing enemy.. " << std::endl;

    _path = path;
    _speed = speed;
    _isDead = false;
    _atGoal = false;

    std::cout << "Enemy path:\n";
    for(const auto &node : _path) {
        std::cout << "Id:" << node->getId() << " x:" << node->getX() << " y:" << node->getY() << std::endl; 
    }
}

void Enemy::run()
{
    // start at the first node
    std::vector<std::shared_ptr<Node>>::iterator fromNode = _path.begin();
    std::vector<std::shared_ptr<Node>>::iterator toNode = _path.begin();

    toNode++;

    double x1 = fromNode->get()->getX();
    double y1 = fromNode->get()->getY();
    double x2 = toNode->get()->getX();
    double y2 = toNode->get()->getY();
    std::cout << "Enemy moving between nodes: (" << x1 << "," << y1 << "), (" << x2 << "," << y2 << ")\n";
    double distanceBetweenNodes = std::sqrt(std::pow((x1 - x2), 2) + (std::pow((y1 - y2), 2)));
    std::cout << "Distance between nodes: " << distanceBetweenNodes << std::endl;

    // start clock for movement calculation
    auto lastUpdate = std::chrono::system_clock::now(); 

    while(!_isDead && !_atGoal)
    {
        // sleep 1ms to lower CPU demand
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // calculate time difference
        long timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        if(timeDifference >= 1)
        {
            // determine how far along the path between the nodes we are
            _posNodes += _speed * timeDifference / 1000.0;

            // get distance between the nodes
            double distanceTravelledRatio = _posNodes / distanceBetweenNodes;
            std::cout << "Speed: " << _speed << " Time Diff: " << timeDifference << " Pos between nodes: " << _posNodes << " Distance ratio: " << distanceTravelledRatio << std::endl;

            _x = (((1 - distanceTravelledRatio) * (x1 + (distanceTravelledRatio * x2))));
            _y = (((1 - distanceTravelledRatio) * (y1 + (distanceTravelledRatio * y2))));
        }
        // reset last update to current time
        lastUpdate = std::chrono::system_clock::now();

    }
}
