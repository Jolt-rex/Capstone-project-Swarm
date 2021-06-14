#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Entity.h"

class Model
{
    public:
        // constructor
        Model(std::string map);

        // getter / setters
        std::vector<std::shared_ptr<Entity> > &getEntities();

    private:
        // private members
        std::vector<std::shared_ptr<Entity> > _entities;
};

#endif