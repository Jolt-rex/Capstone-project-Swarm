#ifndef PATH_H
#define PATH_H

#include <vector>
#include <memory>
#include "Intersection.h"

// forward declaration
class Intersection;

// A path between two intersections which are stored in a vector
class Path : public std::enable_shared_from_this<Path> {
    public:
        Path();
    
        // getters / setters
        double getLenth() { return _length; }
        void addFirst(std::shared_ptr<Intersection> intersection);
        void addSecond(std::shared_ptr<Intersection> intersection);
        std::shared_ptr<Intersection> getFirst() { return _first; }
        std::shared_ptr<Intersection> getSecond() { return _second; }

        std::shared_ptr<Path> get_shared_this() { return shared_from_this(); }

    private:
        float _length;
        std::shared_ptr<Intersection> _first;
        std::shared_ptr<Intersection> _second;
};

#endif