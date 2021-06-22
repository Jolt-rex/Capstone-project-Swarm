#include <string>
#include <iostream>
#include "Model.h"
#include "Entity.h"
#include "Node.h"
#include "libs/pugixml.hpp"


Model::Model(std::string map)
{
    std::string filename("../maps/" + map + ".xml");
    pugi::xml_document input;
    if(!input.load_file(filename.c_str())) {
        std::cerr << "Unable to load input file, please check map name is correct." << std::endl;
        return;
    }

    // load nodes
    for(const auto &node : input.select_nodes("/node")) {
        int id = std::stoi(node.node().attribute("id").as_string());
        int x = std::stoi(node.node().attribute("x").as_string());
        int y = std::stoi(node.node().attribute("y").as_string());
        
        bool isGoal = id == 0 ? true : false;
        bool isSpawnPoint = node.node().attribute("spawn") ? true : false;

        _nodes.emplace_back(std::make_shared<Node>(id, x, y, isGoal, isSpawnPoint));
    }

    // connect nodes
    for(const auto &path : input.select_nodes("/path")) {
        //int id = std::stoi(path.node().attribute("id").as_string());
        int first = std::stoi(path.node().attribute("first").as_string());
        int second = std::stoi(path.node().attribute("second").as_string());

        // find the intersections defined by the path
        std::shared_ptr<Node> firstNode, secondNode;
        for(const auto &node : _nodes) {
            if(node->getId() == first)
                firstNode = node;
            if(node->getId() == second)
                secondNode = node;
        }

        // cross link the nodes to each other using shared_ptr's
        firstNode->addConnected(secondNode);
        secondNode->addConnected(firstNode);
    }
}

std::vector<std::shared_ptr<Node> > Model::getNodes()
{
    return _nodes;
}
