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
        Enemy(int id, int speed, std::vector<std::shared_ptr<Node>> _path);
        std::vector<std::shared_ptr<Node>> getRoute() { return _route; }
        
    private:
        int _speed;
        double _distance = 0.0f;

        std::shared_ptr<Node> _target;
        std::vector<std::shared_ptr<Node>> _route;

        // access to the model for calculating route
        std::shared_ptr<Model> _model;
};

#endif