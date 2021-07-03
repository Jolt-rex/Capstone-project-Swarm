#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <math.h>

#include "Entity.h"
#include "Tower.h"

#define TOWER_RELOAD_TIME 1000

Tower::Tower(int id, double x, double y, int range, std::weak_ptr<Model> model) : Entity(id, x, y)
{
    std::cout << "Creating tower #" << id << std::endl;
    _model = model;
    _range = range;
    _active = false;
    this->simulate();
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
    while(_active)
    {
        std::unique_lock<std::mutex> u_lock(Tower::_mutex);
        u_lock.unlock();
        
        double enemy_x;
        double enemy_y;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        auto timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastMissile).count();

        //std::cout << "Time diff: " << timeDifference << std::endl;
        
        u_lock.lock();
        if(timeDifference >= TOWER_RELOAD_TIME)
        {          
            // convert weak_ptr to shared_ptr and check it for null
            if(auto model = _model.lock())
            {
                // iterate over the enemies and check if there are any that are untargeted
                for(auto &enemy : model->_enemies)
                {
                    if(enemy && !enemy->isTargeted()) // && (enemy_x = enemy->getX()) && (enemy_y = enemy->getY())))
                    {
                        enemy_x = enemy->getX();
                        enemy_y = enemy->getY();
                        // check target is in range
                        double distance = std::sqrt(std::pow((_x - enemy_x), 2) + (std::pow((_y - enemy_y), 2)));
                        if(_range >= distance)
                        {
                            enemy->setTargeted(true);
                            lastMissile = std::chrono::system_clock::now();
                            std::unique_ptr<Missile> missile = std::make_unique<Missile>(99, _x, _y, 150, enemy);
                            model->moveMissileToModel(missile);
                            break;
                        }   
                    }
                }
            }
        }
    }
}

