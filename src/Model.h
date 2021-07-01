#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include "Entity.h"
#include "Node.h"
#include "Enemy.h"
#include "Tower.h"
#include "Missile.h"

class Enemy;
class Tower;
class Missile;

enum GameState {
    kRunning, kWon, kLost
};

class Model
{
    public:
        // constructor
        Model(std::string map);

        // getter / setters
        std::vector<std::shared_ptr<Node>> getNodes() { return _nodes; }
        std::shared_ptr<Node> getGoal() { return _goal; }
        GameState getGameState() { return _gameState; }
        void setGameState(GameState gs) { _gameState = gs; }

        void moveEnemyToModel(std::shared_ptr<Enemy> &enemy);
        void moveMissileToModel(std::unique_ptr<Missile> &missile);

        void simulate();
        void cleanup();

        std::vector<std::shared_ptr<Enemy>> _enemies;

        std::vector<std::unique_ptr<Tower>> _towers;
        std::vector<std::unique_ptr<Missile>> _missiles;

    private:
        // private members
        std::vector<std::shared_ptr<Node>> _nodes;
        std::shared_ptr<Node> _goal;

        
        GameState _gameState; 
        std::mutex _mutex;
        std::thread _thread;
};

#endif