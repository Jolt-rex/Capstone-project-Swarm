#ifndef MISSILE_H
#define MISSILE_H

#include <memory>
#include "Enemy.h"
#include "Entity.h"

class Enemy;

class Missile : public Entity
{
    public:
        Missile(int id, int x, int y, int speed, std::shared_ptr<Enemy> &target);
        ~Missile();

        void simulate();
        void launch();
        void destroy();

    private:
        int _speed;
        bool _destroyed;
        std::shared_ptr<Enemy> _target;
    

};

#endif