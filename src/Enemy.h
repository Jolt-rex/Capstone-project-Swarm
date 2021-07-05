#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include <vector>
#include <mutex>
#include "Model.h"
#include "Node.h"
#include "Entity.h"

class Model;

// Enemy class inherits from Entity
class Enemy : public Entity
{
    public:
        // constructor
        Enemy(int id, int speed, std::vector<std::shared_ptr<Node>> _path);
        ~Enemy();

        // getter / setter
        bool isTargeted();
        void setTargeted(bool targeted);
        bool isDead();
        void setToDead();
        bool atGoal();
        
        std::vector<std::shared_ptr<Node>> getRoute() { return _path; }

        void simulate();
        void run();
        
    private:
        int _speed;
        double _distance = 0.0;
        double _posNodes = 0.0;
        bool _isDead;
        bool _atGoal;
        bool _isTargeted;

        std::vector<std::shared_ptr<Node>> _path;
};

#endif