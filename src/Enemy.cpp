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
    // std::cout << "Constructing enemy #" << id << " path length: " << path.size() << std::endl;

    _path = path;
    _speed = speed;
    _isDead = false;
    _isTargeted = false;
    _atGoal = false;
}

Enemy::~Enemy()
{
    std::cout << "Enemy #" << _id << " destroyed" << std::endl;
}

bool Enemy::isTargeted()
{
    std::unique_lock<std::mutex> u_lock(_mutex);
    return _isTargeted;
}

void Enemy::setTargeted(bool targeted)
{
    std::unique_lock<std::mutex> u_lock(_mutex);
    _isTargeted = targeted;
}

bool Enemy::isDead()
{
    std::unique_lock<std::mutex> u_lock(_mutex);
    return _isDead; 
}

void Enemy::setToDead()
{   
    std::unique_lock<std::mutex> u_lock(_mutex);
    _isDead = true;
}

void Enemy::simulate()
{
    // begin run function in it's own thread on this object
    _threads.emplace_back(std::thread(&Enemy::run, this));
}

void Enemy::run()
{
    // allocate iterators to the first and second nodes to move between
    std::vector<std::shared_ptr<Node>>::iterator fromNode = _path.begin();
    std::vector<std::shared_ptr<Node>>::iterator toNode = _path.begin();
    toNode++;

    // start clock for movement calculation
    auto lastUpdate = std::chrono::system_clock::now(); 

    std::unique_lock<std::mutex> u_lock(_mutex);
    // get the x and y values for nodes we are moving between    
    double x1 = fromNode->get()->getX();
    double y1 = fromNode->get()->getY();
    double x2 = toNode->get()->getX();
    double y2 = toNode->get()->getY();
    u_lock.unlock();

    double distanceBetweenNodes = std::sqrt(std::pow((x1 - x2), 2) + (std::pow((y1 - y2), 2)));

    u_lock.lock();
    while(!_atGoal && !_isDead)
    {
        u_lock.unlock();
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
            //std::cout << "Speed: " << _speed << " Time Diff: " << timeDifference << " Pos between nodes: " << _posNodes << " Distance ratio: " << distanceTravelledRatio << std::endl;

            u_lock.lock();
            _x = x1 + distanceTravelledRatio * (x2 - x1);
            _y = y1 + distanceTravelledRatio * (y2 - y1);

            // if we are 99% of the distance to the toNode
            // iterate to both node references to the next two in the path
            if(distanceTravelledRatio > 0.99) {
                _posNodes = 0.0;
                fromNode++;
                toNode++;
                
                // if we have passed the last node in the path, set the atGoal member to exit the while loop
                if(toNode == _path.end()) { 
                    //std::cout << "Emeny #" << _id << " at goal" << std::endl;
                    _atGoal = true; 
                    break;    
                }

                // update x and y values for nodes we are moving between
                x1 = fromNode->get()->getX();
                y1 = fromNode->get()->getY();
                x2 = toNode->get()->getX();
                y2 = toNode->get()->getY();

                // re calculate distance between the next iteration of node pairs
                distanceBetweenNodes = std::sqrt(std::pow((x1 - x2), 2) + (std::pow((y1 - y2), 2)));
            }
        }
        // reset last update to current time
        lastUpdate = std::chrono::system_clock::now();
    }
    //if(_atGoal) std::cout << "Enemy #" << _id << " reached goal..." << std::endl;
    // end game and set enemy to dead
    //if(_isDead) std::cout << "Enemy #" << _id << " was killed..." << std::endl;
}
