#ifndef TOWER_H
#define TOWER_H

#include <memory>
#include "Entity.h"
#include "Enemy.h"
#include "Model.h"

class Model;
class Enemy;

class Tower : public Entity
{
    public:
        Tower(int id, double x, double y);
        ~Tower();

        void simulate();
        void run();

    private:
        int _missiles;
        std::shared_ptr<Enemy> _target;

        // shared ptr to the model to send destroy message
        std::shared_ptr<Model> _model;
};


#endif