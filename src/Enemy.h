#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include <vector>
#include "Model.h"
#include "Node.h"
#include "Entity.h"

class Enemy : public Entity
{
    public:
        Enemy(int id, float x, float y);

        void ConstructPath();
        
    private:
        int _speed;
        float _distance = 0.0f;

        // route planning members
        std::shared_ptr<Node> _origin;
        std::shared_ptr<Node> _goal;
        std::vector<std::shared_ptr<Node>> _route;

        // access to the model for calculating route
        std::shared_ptr<Model> _model;
};

#endif