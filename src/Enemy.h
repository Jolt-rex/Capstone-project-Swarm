#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include <vector>
#include "Model.h"
#include "Node.h"
#include "Entity.h"

class Model;

class Enemy : public Entity
{
    public:
        // constructor
        Enemy(int id, int speed, std::vector<std::shared_ptr<Node>> _path);
        ~Enemy();

        // getter / setter
        std::vector<std::shared_ptr<Node>> getRoute() { return _path; }
        void setToDead() { _isDead = true; }

        void simulate();
        void run();
        
    private:
        int _speed;
        double _distance = 0.0;
        double _posNodes = 0.0;
        bool _isDead;
        bool _atGoal;

        std::shared_ptr<Node> _goal;
        std::vector<std::shared_ptr<Node>> _path;

        // access to the model for sending message to kill / 
        // remove this enemy from the model when dead
        std::shared_ptr<Model> _model;
};

#endif