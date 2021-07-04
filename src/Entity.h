#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <thread>
#include <mutex>

// Base class for all objects on the map
class Entity
{
    public:
        Entity(int id, double x, double y);
        ~Entity();

        void setLocation(double x, double y);
        int getId() { return _id; }
        const double getX();
        const double getY();

    protected:
        int _id;
        double _x;
        double _y;

        std::vector<std::thread> _threads;
        std::mutex _mutex;
};

#endif