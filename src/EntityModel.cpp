#include <string>
#include <iostream>
#include "EntityModel.h"
#include "libs/pugiconfig.hpp"


EntityModel::EntityModel(std::string map)
{
    std::string filename("../maps/" + map + ".xml");
    pugi::xml_document input;
    if(!input.load_file(filename.c_str())) {
        std::cerr << "Unable to load input file, please check map name is correct." << std::endl;
    }

    std::cout << input.child("intersection") << std::endl;
}

std::vector<std::shared_ptr<Entity> > &EntityModel::getEntities()
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