#include <memory>
#include <vector>
#include <thread>
#include <random>

#include "SpawnController.h"

SpawnController::SpawnController(std::shared_ptr<Model> model)
{
    // generate spawn points from the model
    for(auto sp : model->getNodes())
    {
        if(sp->isSpawnPoint()) {
            _spawnPoints.emplace_back(std::make_unique<SpawnPoint>(model, sp, model->getGoal()));
        }
    }
    _spawnPointCount = _spawnPoints.size();
    _enemyCount = 0;
}

SpawnController::~SpawnController()
{
    _thread.join();
}

void SpawnController::simulate()  
{
    std::cout << "There are " << _spawnPointCount << " spawn points." << std::endl;
    
    _thread = std::thread(&SpawnController::spawnEnemies, this);
}

void SpawnController::spawnEnemies()
{
    _running = true;

    // random variable
    std::mt19937 rng(time(nullptr));
    std::uniform_int_distribution<> dist(0, _spawnPointCount - 1);
    
    // spawn controller loop to spawn enemies at random times
    auto spawnTime = std::chrono::system_clock::now();
    while(_running && _enemyCount < 20) 
    {
        // update every 1/10 of a second
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        // random int of which spawn point to select
        int randomSpawnPoint = dist(rng);

        // std::cout << "Spawning enemy at #" << randomSpawnPoint << std::endl;

        _spawnPoints[randomSpawnPoint]->SpawnEnemy(++_enemyCount, 15);
    } 

}

