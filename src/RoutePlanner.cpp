#include <memory>
#include <vector>
#include "Node.h"
#include "RoutePlanner.h"

RoutePlanner::RoutePlanner(std::shared_ptr<Model> model, std::shared_ptr<Node> origin, std::shared_ptr<Node> goal)
{
    // assign origin and goal nodes
    _origin = origin;
    _goal = goal;
}

// add neighbouring nodes to the open list
void RoutePlanner::AddNeighbours(std::shared_ptr<Node> currentNode)
{
    std::vector<std::shared_ptr<Node>> neighbours = currentNode->GetConnected();
    // for(auto &node : neighbours) {
    //     if()
    // }
}