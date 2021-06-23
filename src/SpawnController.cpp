#include <memory>
#include <vector>

#include "SpawnController.h"

SpawnController::SpawnController(std::shared_ptr<Model> model)
{
    // generate spawn points from the model
    for(auto sp : model->GetNodes())
    {
        if(sp->IsSpawnPoint()) {
            _spawnPoints.emplace_back(std::make_unique<SpawnPoint>(model, sp, model->GetGoal()));
        }
    }
    _spawnPointCount = _spawnPoints.size();
}

void SpawnController::Simulate()
{
    

}

