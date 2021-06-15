#include <iostream>
#include <memory>

#include "Path.h"
#include "Intersection.h"

Path::Path()
{
    std::cout << "Path Constructor" << std::endl;
}

// functions to link the path to the intersection
// then back link the intersection to the path
void Path::addFirst(std::shared_ptr<Intersection> intersection)
{
    _first = intersection;
    intersection->addPath(get_shared_this());
}   

void Path::addSecond(std::shared_ptr<Intersection> intersection)
{
    _second = intersection;
    intersection->addPath(get_shared_this());
}