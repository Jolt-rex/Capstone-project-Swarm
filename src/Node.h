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

        void SetParent(std::shared_ptr<Node> parent) { _parent = parent; }
        std::shared_ptr<Node> GetParent() { return _parent; }

        void SetGValue(double g_value) { _gValue = g_value; }
        double GetGValue() { return _gValue; }

        void SetHValue(double h_value) { _hValue = h_value; }
        double GetHValue() { return _hValue; }
        
        void AddConnected(std::shared_ptr<Node> node);
        std::vector<std::shared_ptr<Node>> GetConnected() const;

        double Distance(std::shared_ptr<Node> node);

    protected:
        bool _goal;
        bool _spawnPoint;

        bool _visited;
        double _hValue;
        double _gValue;
        std::shared_ptr<Node> _parent;

        std::vector<std::shared_ptr<Node>> _connectedNodes;
};


#endif