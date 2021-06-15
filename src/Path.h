#ifndef PATH_H
#define PATH_H

#include <vector>
#include <memory>
#include "Intersection.h"


// A path between two intersections which are stored in a vector
class Path {
    public:
        Path();
        void addIntersection(std::shared_ptr<int> intersection);

    private:
        std::vector<std::shared_ptr<int> > _intersections;
};

#endif