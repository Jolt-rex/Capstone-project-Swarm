#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <math.h>

#include "Entity.h"
#include "Tower.h"
#include "GameRules.h"

Tower::Tower(int id, double x, double y, int range, std::weak_ptr<Model> model) : Entity(id, x, y)
{
    //std::cout << "Creating tower #" << id << std::endl;
    _model = model;
    _active = false;

    if(auto m = model.lock())
    {
        _missileSpeed = m->_gameRules.missileSpeed;
        _missileReloadTime = m->_gameRules.missileReloadTime;
    }
    else
    {
        std::cout << "Unable to load game rules for tower object. Using defaults." << std::endl;
        _missileSpeed = 150;
        _missileReloadTime = 4000;
    }

    this->simulate();
}

Tower::~Tower()
{
    for(auto &thread : _threads)
    {
        thread.join();
    }
    
    //std::cout << "Tower #" << _id << " destroyed" << std::endl;
}

void Tower::simulate()
{
    // std::cout << "Tower starting simulation" << std::endl;
    _threads.emplace_back(std::thread(&Tower::run, this));
}

// while loop
void Tower::run()
{
    // start clock 
    auto lastMissile = std::chrono::system_clock::now(); 

    _active = true;
    std::unique_lock<std::mutex> u_lock(_mutex);
    while(_active)
    {
        u_lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        auto timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastMissile).count();
        
        u_lock.lock();
        
        if(timeDifference >= _missileReloadTime)
        {          
            // convert weak_ptr to shared_ptr and check it for null
            if(auto model = _model.lock())
            {
                // get earliest created enemy that is in range of this tower
                std::shared_ptr<Enemy> enemy = model->getTargetableEnemy(*this);    
                if(enemy)
                {
                    enemy->setTargeted(true);
                    lastMissile = std::chrono::system_clock::now();
                    std::unique_ptr<Missile> missile = std::make_unique<Missile>(99, _x, _y, _missileSpeed, enemy);
                    model->moveMissileToModel(missile);
                    continue;      
                }
                
            }
        }
    }
}

void Tower::deactivateTower()
{
    std::unique_lock<std::mutex> u_lock(_mutex);
    _active = false;
}
