#ifndef SPAWNCONTROLLER_H
#define SPAWNCONTROLLER_H

#include <memory>
#include <vector>
#include <thread>
#include <mutex>

#include "Model.h"
#include "Enemy.h"
#include "SpawnPoint.h"
#include "GameRules.h"

class SpawnPoint;

// One SpawnController object holds pointers to multiple SpawnPoints
// The SpawnController runs a loop where it randomly selects a spawn point
// and calls a function of the SpawnPoint to spawn an enemy at a defined interval
class SpawnController
{
    public:
        SpawnController(std::shared_ptr<Model> model);
        ~SpawnController();
        
        void spawnEnemies();
        void simulate();

    private:
        // vector of spawn points to call method and create enemy
        std::vector<std::unique_ptr<SpawnPoint>> _spawnPoints;

        int _spawnPointCount;
        int _enemyCount;
        bool _running;

        // from model -> GameRules
        int _spawnInterval;
        int _enemiesToSpawn;
        int _enemySpeed;
        int _missileSpeed;
        bool _speedup;

        // thread holder
        std::thread _thread;
        std::mutex _mutex;

        // pointer to model to check gameState ie: kRunning..
        std::shared_ptr<Model> _model;
};

#endif