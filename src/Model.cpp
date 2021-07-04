#include <string>
#include <iostream>
#include <algorithm>
#include <memory>
#include <math.h>
#include "Model.h"
#include "Entity.h"
#include "Node.h"
#include "Enemy.h"
#include "Tower.h"
#include "Missile.h"
#include "GameRules.h"

// 3rd party lib
#include "libs/pugixml.hpp"

Model::Model(GameRules &gameRules)
{
    _gameRules = gameRules;

    std::string filename("../maps/" + gameRules.map + ".xml");
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

void Model::moveEnemyToModel(std::shared_ptr<Enemy> &enemy)
{
    std::unique_lock<std::mutex> u_lock(_mutex);
    _enemies.emplace_back(std::move(enemy));
    _enemies.back()->simulate();
}

 void Model::moveMissileToModel(std::unique_ptr<Missile> &missile)
 {
     std::unique_lock<std::mutex> u_lock(_mutex);
    _missiles.emplace_back(std::move(missile));
    _missiles.back()->simulate();
 }

 std::shared_ptr<Enemy> Model::getTargetableEnemy(Tower &tower)
 {
     std::unique_lock<std::mutex> u_lock(_mutex);
     for(const std::shared_ptr<Enemy> &enemy : _enemies)
     {
         if(!enemy->isTargeted())
         {
            double distance = std::sqrt(std::pow((tower.getX() - enemy->getX()), 2) + (std::pow((tower.getY() - enemy->getY()), 2)));
            
            if(_gameRules.towerRange >= distance)
            {
                return enemy;
            }                
         }
     }
     return nullptr;
 }
 
 void Model::simulate()
 {
    _gameState = GameState::kRunning;
    _funds = _gameRules.startingFunds;
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
        if(_missiles.size() > 0){
            _missiles.erase(std::remove_if(_missiles.begin(), _missiles.end(), [](const std::unique_ptr<Missile> &missile) { 
                if(missile->isDestroyed()) std::cout << "Destroying missile from Model vector" << std::endl;
                return missile->isDestroyed(); 
            }), _missiles.end());
        }
        if(_enemies.size() > 0) {
            _enemies.erase(std::remove_if(_enemies.begin(), _enemies.end(), [&](const std::shared_ptr<Enemy> &enemy) { 
                if(enemy->isDead()) std::cout << "Destroying enemy from Model vector" << std::endl;
                if(enemy->isDead()) _funds += 20;
                return enemy->isDead(); 
            }), _enemies.end());
        }
     }
 }
