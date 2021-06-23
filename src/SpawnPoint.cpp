
#include "SpawnPoint.h"
#include "Model.h"

// When created, the spawn point will generate the path the to the goal node once
// then use this path for all enemies spawned at this location
SpawnPoint::SpawnPoint(std::shared_ptr<Model> model, std::shared_ptr<Node> origin,
                    std::shared_ptr<Node> goal)
{
    _origin = origin;
    _goal = goal;
    
    RoutePlanner rp(model, origin, goal);
    _path = rp.AStarSearch();
}