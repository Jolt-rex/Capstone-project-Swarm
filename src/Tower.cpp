#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

#include "Entity.h"
#include "Tower.h"

Tower::Tower(int id, double x, double y, std::weak_ptr<Model> model) : Entity(id, x, y)
{
    std::cout << "Creating tower #" << id << std::endl;
    _model = model;
    _active = false;
    this->simulate();
}

void Tower::simulate()
{
    std::cout << "Tower starting simulation" << std::endl;
    _threads.emplace_back(std::thread(&Tower::run, this));
}

// while loop
void Tower::run()
{
    std::unique_lock<std::mutex> u_lock(_mutex);
    _active = true;
    while(_active)
    {
        u_lock.unlock();
        // wait 2 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        u_lock.lock();
        // convert weak_ptr to shared_ptr and check it for null
        if(auto model = _model.lock())
        {
            // iterate over the enemies and check if there are any that are untargeted
            for(auto &enemy : model->_enemies)
            {
                if(!enemy->isTargeted())
                {
                    enemy->setTargeted(true);
                    std::unique_ptr<Missile> missile = std::make_unique<Missile>(99, _x, _y, 100, enemy);
                    model->moveMissileToModel(missile);
                    break;
                }
            }
        }
    }
}

