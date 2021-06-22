#ifndef ENTITY_H
#define ENTITY_H

// Base class for all objects on the map
class Entity
{
    public:
        Entity(int id, float x, float y);
        void setLocation(float x, float y);
        int getId() { return _id; }
        float getX() { return _x; }
        float getY() { return _y; }


    protected:
        int _id;
        float _x;
        float _y;
};

#endif