#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include "Node.h"
#include "RoutePlanner.h"

RoutePlanner::RoutePlanner(std::shared_ptr<Model> model, std::shared_ptr<Node> origin, std::shared_ptr<Node> goal)
{
    // assign origin and goal nodes
    _origin = origin;
    _goal = goal;
    std::cout << "Route Planner created.. origin node=" << _origin->getId() << " goal node=" << _goal->getId() << std::endl;
}

// reset the model of nodes, for other route planners to use the pathfinding private members
void RoutePlanner::ResetModel()
{
    for(auto node : _model->getNodes())
    {
        node->SetGValue(0.0);
        node->SetHValue(0.0);
        node->SetVisited(false);
        node->SetParent(nullptr);
    }
}

double RoutePlanner::CalculateHValue(std::shared_ptr<Node> node)
{
    return node->Distance(_goal);
}

// add neighbouring nodes to the open list
void RoutePlanner::AddNeighbours(std::shared_ptr<Node> currentNode)
{
    std::vector<std::shared_ptr<Node>> neighbours = currentNode->getConnected();
    for(auto &node : neighbours) {
        if(!node->HasBeenVisited()) {
            node->SetParent(currentNode);
            node->SetHValue(CalculateHValue(node)); 
            node->SetGValue(node->Distance(currentNode) + currentNode->GetGValue());
            node->SetVisited(true);
            _openList.emplace_back(node);
        }
    }
}

// sorting function, sorts the open_list vector according to h + g values
bool CompareNode(std::shared_ptr<Node> a, std::shared_ptr<Node> b)
{
    double a_value = a->GetGValue() + a->GetHValue();
    double b_value = b->GetGValue() + b->GetHValue();
    return a_value > b_value;
}

std::shared_ptr<Node> RoutePlanner::NextNode() 
{
    std::sort(_openList.begin(), _openList.end(), CompareNode);
    auto lowestNode = _openList.back();
    _openList.pop_back();
    return lowestNode;
}

void RoutePlanner::ConstructFinalPath(std::shared_ptr<Node> node)
{
    _path.clear();

    while(node != nullptr) {
        _path.emplace_back(node);
        node = node->GetParent();
    }

    // reverse path 
    std::reverse(_path.begin(), _path.end());
}

std::vector<std::shared_ptr<Node>> RoutePlanner::AStarSearch()
{  
    std::shared_ptr<Node> currentNode;

    _origin->SetGValue(0.0);
    _origin->SetHValue(CalculateHValue(_origin));
    _origin->SetParent(nullptr);
    _origin->SetVisited(true);
    _openList.push_back(_origin);
    while(_openList.size() > 0)
    {
        currentNode = NextNode();
        if(currentNode->getId() == _goal->getId())
        {
            ConstructFinalPath(currentNode);
            break;
        }
        AddNeighbours(currentNode);
    }

    return _path;
}