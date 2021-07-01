#include <string>
#include <iostream>
#include <algorithm>
#include <memory>
#include "Model.h"
#include "Entity.h"
#include "Node.h"
#include "Enemy.h"
#include "Tower.h"
#include "Missile.h"
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
    _gameState = GameState::kRunning;
}

void Model::moveEnemyToModel(std::shared_ptr<Enemy> &enemy)
{
    _enemies.emplace_back(std::move(enemy));
    _enemies.back()->simulate();
}

// find the enemy with the model referece to it and remove it from the vector
// the shared_ptr will go out of scope and the object will be destroyed
// once the missile shared_ptr is destroyed also
// this means we must ensure only one missle can target the enemy at any time
void Model::killEnemy(int id)
 {
    auto enemy = std::find_if(_enemies.begin(), _enemies.end(), [id](std::shared_ptr<Enemy> &e) { return e->getId() == id; });
    if(enemy != _enemies.end()) 
        _enemies.erase(enemy);
 }

 void Model::moveMissileToModel(std::unique_ptr<Missile> &missile)
 {
    _missiles.emplace_back(std::move(missile));
    _missiles.back()->simulate();
 }

 void Model::destroyMissile(int id)
 {
     auto missile = std::find_if(_missiles.begin(), _missiles.end(), [id](std::unique_ptr<Missile> &m) { return m->getId() == id; });
     if(missile != _missiles.end())
        _missiles.erase(missile);
 }
 
 void Model::simulate()
 {
     _thread = std::thread(&Model::cleanup, this);
 }

// iterate over enemies and missiles and remove if dead / destroyed
 void Model::cleanup()
 {
     std::unique_lock<std::mutex> u_lock(_mutex);
     while(_gameState == kRunning)
     {
        u_lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        u_lock.lock();
        _enemies.erase(std::remove_if(_enemies.begin(), _enemies.end(), [](const std::shared_ptr<Enemy> &enemy) { return enemy->isDead(); }));
        _missiles.erase(std::remove_if(_missiles.begin(), _missiles.end(), [](const std::unique_ptr<Missile> &missile) { return missile->isDestroyed(); }));
     }
 }
