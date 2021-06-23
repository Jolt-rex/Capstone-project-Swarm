#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Entity.h"
#include "Node.h"
#include "Enemy.h"

class Enemy;

class Model
{
    public:
        // constructor
        Model(std::string map);

        // getter / setters
        std::vector<std::shared_ptr<Node>> GetNodes() { return _nodes; }
        std::shared_ptr<Node> GetGoal() { return _goal; }

        void MoveEnemyToModel(std::unique_ptr<Enemy> enemy);
        void KillEnemy(int id);

    private:
        // private members
        std::vector<std::shared_ptr<Node>> _nodes;
        std::shared_ptr<Node> _goal;

        std::vector<std::unique_ptr<Enemy>> _enemies;
};

#endif