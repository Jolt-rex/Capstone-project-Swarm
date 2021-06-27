#include <memory>
#include <vector>
#include <thread>

#include "SpawnController.h"

SpawnController::SpawnController(std::shared_ptr<Model> model)
{
    // generate spawn points from the model
    for(auto sp : model->getNodes())
    {
        if(sp->isSpawnPoint()) {
            _spawnPoints.emplace_back(std::make_unique<SpawnPoint>(model, sp, model->GetGoal()));
        }
    }
    _spawnPointCount = _spawnPoints.size();
    _enemyCount = 0;
}

void SpawnController::simulate()  
{
    std::cout << "There are " << _spawnPointCount << " spawn points." << std::endl;
    _running = true;
    
    // spawn controller loop to spawn enemies at random times
    auto spawnTime = std::chrono::system_clock::now();
    while(_running) 
    {
        // update every 1/10 of a second
        std::this_thread::sleep_for(std::chrono::milliseconds(4000));
        if(_enemyCount < 3) _spawnPoints.front()->SpawnEnemy(++_enemyCount, 8);
    }    
}

