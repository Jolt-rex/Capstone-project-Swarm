#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Entity.h"
#include "Node.h"

class Model
{
    public:
        // constructor
        Model(std::string map);

        // getter / setters
        std::vector<std::shared_ptr<Node>> getNodes();

    private:
        // private members
        std::vector<std::shared_ptr<Node>> _nodes;
        std::shared_ptr<Node> _goal;
};

#endif