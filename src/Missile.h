#ifndef MISSILE_H
#define MISSILE_H

#include <memory>
#include "Enemy.h"
#include "Entity.h"
#include "Model.h"

class Enemy;
class Model;

class Missile : public Entity
{
    public:
        Missile(int id, int x, int y, int speed, std::weak_ptr<Enemy> target, std::weak_ptr<Model> model);
        ~Missile();

        void simulate();
        void launch();
        void destroy();

    private:
        int _speed;
        bool _destroyed;
        std::weak_ptr<Enemy> _target;
        std::weak_ptr<Model> _model;
};

#endif