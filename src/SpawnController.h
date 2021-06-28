#ifndef SPAWNCONTROLLER_H
#define SPAWNCONTROLLER_H

#include <memory>
#include <vector>
#include <thread>
#include "Model.h"
#include "Enemy.h"
#include "SpawnPoint.h"

class SpawnController
{
    public:
        SpawnController(std::shared_ptr<Model> model);
        ~SpawnController();
        
        void spawnEnemies();
        void simulate();

    private:
        std::vector<std::unique_ptr<SpawnPoint>> _spawnPoints;
        int _spawnPointCount;
        int _enemyCount;
        bool _running;

        // thread holder
        std::thread _thread;
};

#endif