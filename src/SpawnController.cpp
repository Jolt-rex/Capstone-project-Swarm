#include <memory>
#include <vector>
#include <thread>
#include <random>

#include "SpawnController.h"

// One SpawnController object holds pointers to multiple SpawnPoints
// The SpawnController runs a loop where it randomly selects a spawn point
// and calls a function of the SpawnPoint to spawn an enemy when required
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

    _spawnInterval = model->_gameRules.enemySpawnInterval;
    _enemiesToSpawn = model->_gameRules.maxEnemiesToSpawn;
    _enemySpeed = model->_gameRules.enemySpeed;   
    _missileSpeed = model->_gameRules.missileSpeed; 
    _speedup = model->_gameRules.speedup;

    _model = model;
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
    // random variable
    std::mt19937 rng(time(nullptr));
    std::uniform_int_distribution<> dist(0, _spawnPointCount - 1);
    
    // spawn controller loop to spawn enemies at random locations
    while(_model->getGameState() == kRunning && _enemyCount < _enemiesToSpawn) 
    {

        // random int of which spawn point to select
        int randomSpawnPoint = dist(rng);

        //std::cout << "Spawning enemy at #" << randomSpawnPoint << std::endl;
        _spawnPoints[randomSpawnPoint]->SpawnEnemy(++_enemyCount, _enemySpeed);

        // if speedup is activated
        // every third enemy, increase enemy speed and decrease spawn interval
        if(_speedup && (_enemyCount % 3 == 0))
        {
            //std::cout << "Enemy speed: " << _enemySpeed << " Spawn Interval: " << _spawnInterval << std::endl;
            // dont let enemies spawn faster than every 100ms
            if(_spawnInterval >= 110) 
            {
                _spawnInterval -= 10;
            }

            // dont allow the enemy to be faster than 60% of the missile speed
            if(_enemySpeed < _missileSpeed * 0.6)
            {
                _enemySpeed++;
            }
        }

        // sleep for spawnInterval - then restart loop
        std::this_thread::sleep_for(std::chrono::milliseconds(_spawnInterval));
    } 
}

