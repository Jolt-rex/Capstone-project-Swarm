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
}

void SpawnController::Simulate()
{
    std::cout << "There are " << _spawnPointCount << " spawn points." << std::endl;

    std::thread threadEnemy(&SpawnPoint::SpawnEnemy, _spawnPoints.front().get(), 1, 4);
    //_spawnPoints.front()->SpawnEnemy(1, 4);
    threadEnemy.join();
}

