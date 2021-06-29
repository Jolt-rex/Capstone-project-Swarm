
#include <memory>
#include <iostream>
#include <thread>
#include <math.h>

#include "Missile.h"

Missile::Missile(int id, int x, int y, int speed, std::shared_ptr<Enemy> &target) : Entity(id, x, y)
{
    _destroyed = false;
    _speed = speed;
    _target = target;
    std::cout << "Missle #" << id << " created" << std::endl;
}

Missile::~Missile()
{
    std::cout << "Destroying missile #" << _id << std::endl;
}

void Missile::simulate()
{
    _threads.emplace_back(std::thread(&Missile::launch, this));
}

void Missile::launch()
{
    double initialVelocity[] { 0.0, 4.0 };


    // start clock for movement calculation
    auto lastUpdate = std::chrono::system_clock::now(); 

    // while loop for missle movement // event handling
    while(!_destroyed)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        
        // move towards target
        long timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        double position = 0.0;

        if(timeDifference >= 1)
        {
            double distanceToTarget = std::sqrt(std::pow((_x - _target->getX()), 2) + (std::pow((_y - _target->getY()), 2)));

            position += _speed * timeDifference / 1000.0;

            double distanceTravelledRatio = position / distanceToTarget;

            _x = _x + distanceTravelledRatio * (_target->getX() - _x);
            _y = _y + distanceTravelledRatio * (_target->getY() - _y);
        }

        lastUpdate = std::chrono::system_clock::now();
    }
}

            
                // // if we are 99% of the distance to the toNode
                // // iterate to both node references to the next two in the path
                // if(distanceTravelledRatio > 0.99) {
                //     _posNodes = 0.0;
                //     fromNode++;
                //     toNode++;
                    
                //     // if we have passed the last node in the path, set the atGoal member to exit the while loop
                //     if(toNode == _path.end()) { 
                //         _atGoal = true; 
                //         break;    
                //     }

                //     // update x and y values for nodes we are moving between
                //     x1 = fromNode->get()->getX();
                //     y1 = fromNode->get()->getY();
                //     x2 = toNode->get()->getX();
                //     y2 = toNode->get()->getY();

                //     // re calculate distance between the next iteration of node pairs
                //     distanceBetweenNodes = std::sqrt(std::pow((x1 - x2), 2) + (std::pow((y1 - y2), 2)));



void Missile::destroy()
{
    _destroyed = true;
}

