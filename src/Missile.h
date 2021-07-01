#ifndef MISSILE_H
#define MISSILE_H

#include <memory>
#include <thread>
#include <mutex>
#include "Enemy.h"
#include "Entity.h"
#include "Model.h"

class Enemy;
class Model;

class Missile : public Entity
{
    public:
        Missile(int id, int x, int y, int speed, std::shared_ptr<Enemy> target);
        ~Missile();

        bool isDestroyed() { return _destroyed; }

        void simulate();
        void launch();
        void destroy();

    private:

        std::mutex _mutex;
        int _speed;
        bool _destroyed;
        std::shared_ptr<Enemy> _target;
};

#endif