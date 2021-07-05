#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <thread>
#include <mutex>

// Base class for all objects on the map
class Entity
{
    public:
        // Constructor / destructor
        Entity(int id, double x, double y);
        ~Entity();

        void setLocation(double x, double y);
        int getId() { return _id; }
        const double getX();
        const double getY();

    protected:
        // id of the object and x and y co-ordinates on the screen
        // double has been used even though an int would be suitable
        // to represent the actual position in pixels, a double lets 
        // interpolate the position during the simulation loop
        int _id;
        double _x;
        double _y;

        std::vector<std::thread> _threads;
        std::mutex _mutex;
};

#endif