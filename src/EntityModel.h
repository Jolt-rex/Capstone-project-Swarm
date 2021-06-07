#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "entity.h"
#include "libs/pugixml.hpp"

class EntityModel
{
    public:
        // constructor
        EntityModel(std::string map);

        // getter / setters
        std::vector<std::shared_ptr<Entity> > &getEntities();

    private:
        // private members
        std::vector<std::shared_ptr<Entity> > _entities;
};

#endif