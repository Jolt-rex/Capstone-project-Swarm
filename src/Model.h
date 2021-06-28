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
        std::vector<std::shared_ptr<Node>> getNodes() { return _nodes; }
        std::shared_ptr<Node> getGoal() { return _goal; }

        void moveEnemyToModel(std::unique_ptr<Enemy> enemy);
        void killEnemy(int id);

        std::vector<std::unique_ptr<Enemy>> _enemies;
    private:
        // private members
        std::vector<std::shared_ptr<Node>> _nodes;
        std::shared_ptr<Node> _goal;

};

#endif