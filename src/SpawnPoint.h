#ifndef SPAWNPOINT_H
#define SPAWNPOINT_H

#include <vector>
#include <memory>
#include "Node.h"
#include "RoutePlanner.h"
#include "Enemy.h"

class SpawnPoint
{
    private:
        std::shared_ptr<Node> _goal;
        std::shared_ptr<Node> _origin;

        std::vector<std::shared_ptr<Node>> _path;
};

#endif