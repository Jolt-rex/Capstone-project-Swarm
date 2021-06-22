#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include <vector>
#include <memory>
#include <iostream>
#include "math.h"
#include "Model.h"
#include "Node.h"

// forward declaration
class Node;

class RoutePlanner
{
    public:
        RoutePlanner(std::shared_ptr<Model> model, std::shared_ptr<Node> origin, std::shared_ptr<Node> goal);

        // add neighbouring nodes to the open list
        void RoutePlanner::AddNeighbours(std::shared_ptr<Node> currentNode);

    private:
        std::shared_ptr<Model> _model;

        std::vector<std::shared_ptr<Node>> _openList;
        std::vector<std::shared_ptr<Node>> _path;

        std::shared_ptr<Node> _origin;
        std::shared_ptr<Node> _goal;
};

#endif