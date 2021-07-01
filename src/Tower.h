#ifndef TOWER_H
#define TOWER_H

#include <memory>
#include <thread>
#include <mutex>
#include "Entity.h"
#include "Enemy.h"
#include "Model.h"

class Model;
class Enemy;

class Tower : public Entity
{
    public:
        Tower(int id, double x, double y, std::weak_ptr<Model> model);

        void simulate();
        void run();

        void deactivateTower() { _active = false; }

    private:
        int _missiles;

        // weak ptr to the model. using weak pointer to avoid circular relationship
        std::weak_ptr<Model> _model;
        bool _active;

        std::mutex _mutex;
};


#endif