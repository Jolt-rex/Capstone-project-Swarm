#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

#include "Entity.h"
#include "Tower.h"

Tower::Tower(int id, double x, double y) : Entity(id, x, y)
{
    std::cout << "Creating tower #" << id << std::endl;
    this->simulate();
}

Tower::~Tower()
{
    std::for_each(_threads.begin(), _threads.end(), [](std::thread &th) { th.join(); });
}

void Tower::simulate()
{
    std::cout << "Tower starting simulation" << std::endl;
    _threads.emplace_back(std::thread(&Tower::run, this));
}

// while loop
void Tower::run()
{
    while(_model->getGameState() == GameState::kRunning)
    {
        // wait 2 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));


    }

}

