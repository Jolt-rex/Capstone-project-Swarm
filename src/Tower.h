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
        Tower(int id, double x, double y, int range, std::weak_ptr<Model> model);

        int getRange() { return _range; }

        void simulate();
        void run();

        void deactivateTower() { _active = false; }

    private:
        int _range;

        // weak ptr to the model. using weak pointer to avoid circular relationship
        std::weak_ptr<Model> _model;
        bool _active;

        std::mutex _mutex;
};


#endif