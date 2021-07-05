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
    _model = model;
    this->resetModel();
    
    //std::cout << "Route Planner created.. origin node=" << _origin->getId() << " goal node=" << _goal->getId() << std::endl;
}

RoutePlanner::~RoutePlanner()
{
    // reset all the path finding values for future use
    // as these values are persistent in the Model->Nodes vector
    this->resetModel();
}

// reset the model of nodes, for other route planners to use the pathfinding private members
void RoutePlanner::resetModel()
{
    for(auto node : _model->getNodes())
    {
        node->SetGValue(0.0);
        node->SetHValue(0.0);
        node->SetVisited(false);
        node->SetParent(nullptr);
    }
}

double RoutePlanner::calculateHValue(std::shared_ptr<Node> node)
{
    return node->distance(_goal);
}

// add neighbouring nodes to the open list
void RoutePlanner::addNeighbours(std::shared_ptr<Node> currentNode)
{
    // we are using weak_ptr's to avoid nodes pointing to each other with shared_ptr
    // and creating circular dependancies. The nodes persist in memory as the Model 
    // object has a vector of shared_ptr's to all nodes
    std::vector<std::weak_ptr<Node>> neighbours = currentNode->getConnected();
    for(auto &neighbour : neighbours) {
        if(auto node = neighbour.lock())
        {
            if(!node->HasBeenVisited()) {
                node->SetParent(currentNode);
                node->SetHValue(calculateHValue(node)); 
                node->SetGValue(node->distance(currentNode) + currentNode->GetGValue());
                node->SetVisited(true);
                _openList.emplace_back(node);
            }
        }
    }
}

// sorting function, sorts the open_list vector according to h + g values
bool compareNode(std::shared_ptr<Node> a, std::shared_ptr<Node> b)
{
    double a_value = a->GetGValue() + a->GetHValue();
    double b_value = b->GetGValue() + b->GetHValue();
    return a_value > b_value;
}

std::shared_ptr<Node> RoutePlanner::nextNode() 
{
    std::sort(_openList.begin(), _openList.end(), compareNode);
    auto lowestNode = _openList.back();
    _openList.pop_back();
    return lowestNode;
}

void RoutePlanner::constructFinalPath(std::shared_ptr<Node> node)
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
    _origin->SetHValue(calculateHValue(_origin));
    _origin->SetParent(nullptr);
    _origin->SetVisited(true);
    _openList.push_back(_origin);
    while(_openList.size() > 0)
    {
        currentNode = nextNode();
        if(currentNode->getId() == _goal->getId())
        {
            constructFinalPath(currentNode);
            break;
        }
        addNeighbours(currentNode);
    }

    return _path;
}