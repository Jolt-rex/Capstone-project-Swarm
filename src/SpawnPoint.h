#ifndef SPAWNPOINT_H
#define SPAWNPOINT_H

#include <vector>
#include <memory>
#include "Node.h"
#include "Model.h"
#include "RoutePlanner.h"
#include "Enemy.h"

class SpawnPoint
{
    public:
        SpawnPoint(std::shared_ptr<Model> model, 
                    std::shared_ptr<Node> origin,
                    std::shared_ptr<Node> goal);

    private:
        std::shared_ptr<Node> _goal;
        std::shared_ptr<Node> _origin;

        std::vector<std::shared_ptr<Node>> _path;
};

#endif