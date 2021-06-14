#include <string>
#include <iostream>
#include "Model.h"
#include "Entity.h"
#include "libs/pugixml.hpp"


Model::Model(std::string map)
{
    std::string filename("../maps/" + map + ".xml");
    pugi::xml_document input;
    if(!input.load_file(filename.c_str())) {
        std::cerr << "Unable to load input file, please check map name is correct." << std::endl;
    }

    // load intersections
    for(const auto &node : input.select_nodes("/intersection")) {
        int id = std::stoi(node.node().attribute("id").as_string());
        int x = std::stoi(node.node().attribute("x").as_string());
        int y = std::stoi(node.node().attribute("y").as_string());
        
        if(id > 0) {
            if(node.node().attribute("spawn")) {
                std::cout << "Generating spawn for id: " << id << std::endl;
                Entity new_entity = Entity(id, x, y);
                _entities.emplace_back(&new_entity);
            }
            else {
                std::cout << "Generating intersection for id: " << id << std::endl;
                Entity new_entity = Entity(id, x, y);
                _entities.emplace_back(&new_entity);
            }    
            continue;
        }
        
        // goal node
        if(id == 0) {
            std::cout << "Generating goal entity for id: " << id << std::endl;
            Entity new_entity = Entity(id, x, y);
            // TODO: make this a goal object
            _entities.emplace_back(&new_entity);
            continue;
        }



        std::cout << "x= " << x << " y= " << y << std::endl;
    }
}

std::vector<std::shared_ptr<Entity> > &Model::getEntities()
{
    return _entities;
}

/*
pugi::xml_document doc;

pugi::xml_parse_result result = doc.load_file("tree.xml");

std::cout << "Load result: " << result.description() 
<< ", mesh name: " 
<< doc.child("mesh").attribute("name").value() << std::endl;
*/