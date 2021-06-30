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
    _active = true;
    while(_active)
    {
        // wait 2 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));


        // convert weak_ptr to shared_ptr and check it for null
        if(auto model = _model.lock())
        {
            if(model->_enemies.size() > 0)
            {
                std::unique_ptr<Missile> missile = std::make_unique<Missile>(99, _x, _y, 100, model->_enemies.back(), _model);
                model->moveMissileToModel(missile);
            }
        }
    }
}

