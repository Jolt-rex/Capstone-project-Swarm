
#include <memory>
#include <iostream>
#include <thread>
#include <math.h>
#include <algorithm>
#include "Missile.h"

Missile::Missile(int id, int x, int y, int speed, std::shared_ptr<Enemy> target) : Entity(id, x, y)
{
    _destroyed = false;
    _speed = speed;
    _target = std::move(target);

    // std::cout << "Missle #" << id << " created" << std::endl;
}

Missile::~Missile()
{
    // join the threads
    std::for_each(_threads.begin(), _threads.end(), [](std::thread &th) { th.join(); });
        
    //std::cout << "Destroying missile #" << _id << std::endl;
}

// start the thread for this missile
void Missile::simulate()
{
    // std::cout << "Simulating missile.. " << std::endl;
    _threads.emplace_back(std::thread(&Missile::launch, this));
}

void Missile::launch()
{
    // start clock for movement calculation
    auto lastUpdate = std::chrono::system_clock::now(); 

    std::unique_lock<std::mutex> u_lock(_mutex);
    
    // while loop for missle movement 
    while(!_destroyed && !_target->isDead())
    {
        u_lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        
        // move towards target
        long timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        double position = 0.0;

        if(timeDifference >= 1)
        {
            // get our variables while locked se we can unlock to do the match calculations
            u_lock.lock();
            double x = _x;
            double y = _y;
            double t_x = _target->getX();
            double t_y = _target->getY();
            
            // unlock while we perform heavy math calculations
            u_lock.unlock();

            double distanceToTarget = std::sqrt(std::pow((x - t_x), 2) + (std::pow((y - t_y), 2)));

            position += _speed * timeDifference / 1000.0;

            double distanceTravelledRatio = position / distanceToTarget;

            x = x + distanceTravelledRatio * (t_x - x);
            y = y + distanceTravelledRatio * (t_y - y);

            u_lock.lock();
            _x = x;
            _y = y;            
            
            // if we are 99% the distance to the enemy destroy the enemy and the missile
            if(distanceTravelledRatio > 0.99)
            {
                _target->setToDead();
                _destroyed = true;
            }
        }
                   
        lastUpdate = std::chrono::system_clock::now();
    }
    // if we get here, either target is destroyed or missile is destroyed. 
    // must make sure missile is then destroyed, in the event only the target was
    _destroyed = true;
}

void Missile::destroy()
{
    std::unique_lock<std::mutex> u_lock(_mutex);
    _destroyed = true;
}

