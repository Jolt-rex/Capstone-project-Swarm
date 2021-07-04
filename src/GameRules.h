#ifndef GAMERULES_H
#define GAMERULES_H

#include <string>

struct GameRules
{
    std::string map;
    int startingFunds;
    
    int enemySpeed;         // 4 is slow, 100 is fast
    int maxEnemiesToSpawn;
    int enemySpawnInterval; // missilseconds

    int missileSpeed;       // same as enemy speed, about 150 or more
    int missileReloadTime;  // milliseconds
    int towerCost;
    int towerRange;         // in radius pixels
};


// GAMERULES
#endif