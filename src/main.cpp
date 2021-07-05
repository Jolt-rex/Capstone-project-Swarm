#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>

#include "Model.h"
#include "Graphics.h"
#include "SpawnController.h"
#include "GameRules.h"

// Spawn entry point

// Main function
int main(int argc, char** argv) {   

    // GameRules object defines all settings used by the simulation
    GameRules gameRules;
    gameRules.map = "brisbane";             // map name - requires a .png and .xml file in maps folder
    gameRules.startingFunds = 400;          // starting funds
    gameRules.enemySpeed = 10;              // enemy starting speed 10 is slow, 100 is fast
    gameRules.maxEnemiesToSpawn = 500;      // once the simulation has spawned this number of enemies, the simulation ends
    gameRules.enemySpawnInterval = 1000;    // milliseconds
    gameRules.missileSpeed = 150;           // same ratio as enemy speed
    gameRules.missileReloadTime = 4000;     // milliseconds, time to reload a missile for each tower
    gameRules.towerCost = 100;              // funds used to buy a tower
    gameRules.towerRange = 175;             // in pixels, by radius
    gameRules.killReward = 15;              // funds received on enemy kill
    gameRules.speedup = true;               // exponentially increase enemy speed and lower spawn interval over time
    
    // load entities from xml file into entities vector of shared ptrs
    std::shared_ptr<Model> model = std::make_shared<Model>(gameRules);
    std::unique_ptr<SpawnController> spawnController = std::make_unique<SpawnController>(model);
    std::unique_ptr<Graphics> graphics = std::make_unique<Graphics>(gameRules.map, model);
    
    // threads are created by each of these objects internally
    graphics->simulate();
    model->simulate();
    spawnController->simulate();

    return 0;
}