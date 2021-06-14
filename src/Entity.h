#ifndef ENTITY_H
#define ENTITY_H

// Base class for all objects on the map
class Entity
{
    public:
        void setLocation(double &x, double &y);

    protected:
        int _x;
        int _y;

};

#endif