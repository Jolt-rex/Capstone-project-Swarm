#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>

#include "Model.h"
#include "Graphics.h"
#include "SpawnController.h"
#include "GameRules.h"

// Main function entry point
int main(int argc, char** argv) {   

    GameRules gameRules;
    gameRules.map = "brisbane";
    gameRules.startingFunds = 400;
    gameRules.enemySpeed = 10;
    gameRules.maxEnemiesToSpawn = 500;      
    gameRules.enemySpawnInterval = 1000;    // milliseconds
    gameRules.missileSpeed = 150;
    gameRules.missileReloadTime = 4000;     // milliseconds 
    gameRules.towerCost = 100;
    gameRules.towerRange = 175;
    gameRules.killReward = 15;
    gameRules.speedup = true;               // increase enemy speed and lower spawn interval over time
    
    // load entities from xml file into entities vector of shared ptrs
    std::shared_ptr<Model> model = std::make_shared<Model>(gameRules);
    std::unique_ptr<SpawnController> spawnController = std::make_unique<SpawnController>(model);
    std::unique_ptr<Graphics> graphics = std::make_unique<Graphics>(gameRules.map, model);
    
    graphics->simulate();
    model->simulate();
    spawnController->simulate();

    return 0;
}