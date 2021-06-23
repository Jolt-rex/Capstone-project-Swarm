#ifndef SPAWNCONTROLLER_H
#define SPAWNCONTROLLER_H

#include <memory>
#include <vector>
#include "Model.h"
#include "Enemy.h"
#include "SpawnPoint.h"

class SpawnController
{
    public:
        SpawnController(std::shared_ptr<Model> model);
        void Simulate();

    private:
        std::vector<std::unique_ptr<SpawnPoint>> _spawnPoints;
        int _spawnPointCount;
};

#endif