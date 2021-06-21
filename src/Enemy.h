#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include "Node.h"
#include "Entity.h"

class Enemy : public Entity
{

    private:
        std::shared_ptr<Node> _goal;
        int _speed;
};

#endif