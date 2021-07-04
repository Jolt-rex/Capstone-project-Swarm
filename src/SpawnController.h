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

class SpawnController
{
    public:
        SpawnController(std::shared_ptr<Model> model);
        ~SpawnController();
        
        void spawnEnemies();
        void simulate();

        void disable();

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

        // thread holder
        std::thread _thread;
        std::mutex _mutex;
};

#endif