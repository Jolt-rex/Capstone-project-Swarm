#include <string>
#include <iostream>
#include <algorithm>
#include <memory>
#include "Model.h"
#include "Entity.h"
#include "Node.h"
#include "Enemy.h"
#include "libs/pugixml.hpp"


Model::Model(std::string map)
{
    std::string filename("../maps/" + map + ".xml");
    pugi::xml_document input;
    if(!input.load_file(filename.c_str())) {
        std::cerr << "Unable to load input file, please check map name is correct." << std::endl;
        return;
    }

    // find spawn points
    std::vector<int> spawnNodeIds;
    for(const auto &spawnPoint: input.select_nodes("/spawn")) {
        spawnNodeIds.push_back(std::stoi(spawnPoint.node().attribute("node").as_string()));
    }

    // load nodes
    for(const auto &node : input.select_nodes("/node")) {
        int id = std::stoi(node.node().attribute("id").as_string());
        int x = std::stoi(node.node().attribute("x").as_string());
        int y = std::stoi(node.node().attribute("y").as_string());
        
        bool isSpawnPoint = false;
        bool isGoal = id == 0 ? true : false;

        if(std::find(spawnNodeIds.begin(), spawnNodeIds.end(), id) != spawnNodeIds.end()) {
            isSpawnPoint = true;
        }

        std::shared_ptr<Node> newNode = std::make_shared<Node>(id, x, y, isGoal, isSpawnPoint);
        _nodes.emplace_back(newNode);
        if(isGoal) { _goal = newNode; }
    }

    // connect nodes
    for(const auto &path : input.select_nodes("/path")) {
        //int id = std::stoi(path.node().attribute("id").as_string());
        int first = std::stoi(path.node().attribute("first").as_string());
        int second = std::stoi(path.node().attribute("second").as_string());

        // find the intersections defined by the path
        // TODO: make this a weak_ptr link between nodes to prevent memory leak
        std::shared_ptr<Node> firstNode, secondNode;
        for(const auto &node : _nodes) {
            if(node->getId() == first)
                firstNode = node;
            if(node->getId() == second)
                secondNode = node;
        }

        // cross link the nodes to each other using shared_ptr's
        firstNode->AddConnected(secondNode);
        secondNode->AddConnected(firstNode);
    }
}

void Model::MoveEnemyToModel(std::unique_ptr<Enemy> enemy)
{
    _enemies.emplace_back(std::move(enemy));
}

// find the enemy in the only referece to it and remove it from the vector
// the unique_ptr will go out of scope and the object will be destroyed
void Model::KillEnemy(int id)
 {
    auto enemy = std::find_if(_enemies.begin(), _enemies.end(), [id](std::unique_ptr<Enemy> &e) { return e->getId() == id; });
    _enemies.erase(enemy);
 }
