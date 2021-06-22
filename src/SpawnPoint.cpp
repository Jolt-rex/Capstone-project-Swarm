
#include "SpawnPoint.h"
#include "Model.h"

SpawnPoint::SpawnPoint(std::shared_ptr<Model> model, std::shared_ptr<Node> origin,
                    std::shared_ptr<Node> goal)
{
    _origin = origin;
    _goal = goal;
    
    RoutePlanner rp(model, origin, goal);
    _path = rp.AStarSearch();
}