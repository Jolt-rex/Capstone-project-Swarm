#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Entity.h"
#include "Intersection.h"

class Model
{
    public:
        // constructor
        Model(std::string map);

        // getter / setters
        std::vector<std::shared_ptr<Intersection>> getIntersections();
        std::vector<std::shared_ptr<Path>> getPaths();

    private:
        // private members
        std::vector<std::shared_ptr<Intersection>> _intersections;
        std::vector<std::shared_ptr<Path>> _paths;
};

#endif