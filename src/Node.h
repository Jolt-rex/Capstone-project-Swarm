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
        Node(int id, double x, double y, bool isGoal, bool isSpawnPoint);

        bool IsGoal() const { return _goal; }
        bool IsSpawnPoint() const { return _spawnPoint; }
        
        bool HasBeenVisited() { return _visited; }
        void SetVisited(bool visited) { _visited = visited; }
        
        void AddConnected(std::shared_ptr<Node> node);
        std::vector<std::shared_ptr<Node>> GetConnected() const;

        // pathfinding functions
        double CalculateHValue(std::shared_ptr<Node> goal);

    protected:
        bool _goal;
        bool _spawnPoint;

        bool _visited;

        std::vector<std::shared_ptr<Node>> _connectedNodes;
};


#endif