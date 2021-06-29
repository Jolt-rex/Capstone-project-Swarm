#ifndef MISSILE_H
#define MISSLE_H

#include <memory>
#include "Enemy.h"
#include "Entity.h"

class Missile : public Entity
{
    public:
        Missile(int id, int x, int y);
        ~Missile();

        void simulate();
        void launch();

    private:
        int _speed;
        bool _isFlying;
        std::shared_ptr<Enemy> _target;
    

};

#endif