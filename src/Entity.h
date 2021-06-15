#ifndef ENTITY_H
#define ENTITY_H

// Base class for all objects on the map
class Entity
{
    public:
        Entity(int id, int x, int y);
        void setLocation(int x, int y);
        int getId() { return _id; }
        int getX() { return _x; }
        int getY() { return _y; }


    protected:
        int _id;
        int _x;
        int _y;
};

#endif