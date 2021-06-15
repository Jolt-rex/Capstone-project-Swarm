#include <string>
#include <iostream>
#include "Model.h"
#include "Entity.h"
#include "Intersection.h"
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
        
        bool isGoal = id == 0 ? true : false;
        bool isSpawnPoint = node.node().attribute("spawn") ? true : false;

        _intersections.emplace_back(std::make_shared<Intersection>(id, x, y, isGoal, isSpawnPoint));
    }
}

std::vector<std::shared_ptr<Intersection> > &Model::getIntersections()
{
    return _intersections;
}

std::vector<std::shared_ptr<Path> > &Model::getPaths()
{
    return _paths;
}
