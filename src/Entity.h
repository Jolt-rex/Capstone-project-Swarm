#ifndef ENTITY_H
#define ENTITY_H

// Base class for all objects on the map
class Entity
{
    public:
        Entity(int id, double x, double y);
        void setLocation(double x, double y);
        int getId() { return _id; }
        double getX() { return _x; }
        double getY() { return _y; }

    protected:
        int _id;
        double _x;
        double _y;
};

#endif