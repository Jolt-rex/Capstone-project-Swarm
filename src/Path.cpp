#include <iostream>
#include <memory>

#include "Path.h"
#include "Intersection.h"

Path::Path()
{
    std::cout << "Path Constructor" << std::endl;
}

void Path::addIntersection(std::shared_ptr<int> intersection)
{
    _intersections.emplace_back(intersection);
}
