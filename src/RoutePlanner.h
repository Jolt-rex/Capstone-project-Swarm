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

// Using A* search algorithm
class RoutePlanner
{
    public:
        RoutePlanner(std::shared_ptr<Model> model, std::shared_ptr<Node> origin, std::shared_ptr<Node> goal);
        ~RoutePlanner();

        void resetModel();

        double calculateHValue(std::shared_ptr<Node> node);
        
        // add neighbouring nodes to the open list
        void addNeighbours(std::shared_ptr<Node> currentNode);
        std::shared_ptr<Node> nextNode();

        void constructFinalPath(std::shared_ptr<Node> node);
        std::vector<std::shared_ptr<Node>> AStarSearch();

    private:
        std::shared_ptr<Model> _model;

        std::vector<std::shared_ptr<Node>> _openList;
        std::vector<std::shared_ptr<Node>> _path;

        std::shared_ptr<Node> _origin;
        std::shared_ptr<Node> _goal;
};

#endif