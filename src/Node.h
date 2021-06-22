#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>
#include "Entity.h"

// forward declaration
class Path;

// Node class holds inherited data from Entity(id, x, y) values, 
// and also defines if it is a goal or a spawn point
class Node : public Entity
{
    public:
        Node(int id, int x, int y, bool isGoal, bool isSpawnPoint);
        bool isGoal() const { return _goal; }
        bool isSpawnPoint() const { return _spawnPoint; }
        void addConnected(std::shared_ptr<Node> node);
        std::vector<std::shared_ptr<Node>> getConnected() const;

    private:
        bool _goal;
        bool _spawnPoint;

        std::vector<std::shared_ptr<Node>> _connectedNodes;
};


#endif