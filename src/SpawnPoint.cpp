#include <memory>

#include "SpawnPoint.h"
#include "Model.h"

// When created, the spawn point will generate the path the to the goal node once
// then use this path for all enemies spawned at this location
SpawnPoint::SpawnPoint(std::shared_ptr<Model> model, std::shared_ptr<Node> origin,
                    std::shared_ptr<Node> goal)
{
    _origin = origin;
    _goal = goal;
    _model = model;
    
    RoutePlanner rp(model, origin, goal);
    _path = rp.AStarSearch();

    std::cout << "Creating spawn point. Start:" << _origin->getId() << " Goal:" << _goal->getId() << " Path length:" << _path.size() << " Model node length:" << _model->getNodes().size() << std::endl;
}

void SpawnPoint::SpawnEnemy(int id, int speed)
{
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(id, speed, _path);
    _model->moveEnemyToModel(enemy);
}