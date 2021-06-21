#include <iostream>
#include <memory>

#include "Path.h"
#include "Node.h"

Path::Path()
{
    //std::cout << "Path Constructor" << std::endl;
}

// functions to link the path to the intersection
// then back link the intersection to the path
void Path::addFirst(std::shared_ptr<Node> node)
{
    _first = node;
    node->addPath(get_shared_this());
}   

void Path::addSecond(std::shared_ptr<Node> node)
{
    _second = node;
    node->addPath(get_shared_this());
}