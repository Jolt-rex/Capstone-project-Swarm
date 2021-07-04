#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include "GameRules.h"
#include "Entity.h"
#include "Node.h"
#include "Enemy.h"
#include "Tower.h"
#include "Missile.h"
#include "SpawnController.h"

class Enemy;
class Tower;
class Missile;

enum GameState {
    kRunning, kWon, kLost
};


class Model
{
    public:
        // constructor / destructor
        Model(GameRules &gameRules);
        ~Model();

        // getter / setters
        std::vector<std::shared_ptr<Node>> getNodes() { return _nodes; }
        std::shared_ptr<Node> getGoal() { return _goal; }
        GameState getGameState() { return _gameState; }
        void setGameState(GameState gs) { _gameState = gs; }
        int getFunds() { return _funds; }
        int getKills() { return _kills; }
        void setFunds(int funds) { _funds = funds; }

        void moveEnemyToModel(std::shared_ptr<Enemy> &enemy);
        void moveMissileToModel(std::unique_ptr<Missile> &missile);

        std::shared_ptr<Enemy> getTargetableEnemy(Tower &tower);

        void simulate();
        void cleanup();
        void gameOver();

        std::vector<std::shared_ptr<Enemy>> _enemies;
        std::vector<std::unique_ptr<Tower>> _towers;
        std::vector<std::unique_ptr<Missile>> _missiles;

        GameRules _gameRules;

    private:
        // private members
        std::vector<std::shared_ptr<Node>> _nodes;
        std::shared_ptr<Node> _goal;

        GameState _gameState;
        int _funds;
        int _kills;

        std::mutex _mutex;
        std::thread _thread;
};

#endif