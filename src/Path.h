#ifndef PATH_H
#define PATH_H

#include <vector>
#include <memory>
#include "Node.h"

// forward declaration
class Node;

// A path between two intersections which are stored in a vector
class Path : public std::enable_shared_from_this<Path> {
    public:
        Path();
    
        // getters / setters
        double getLenth() { return _length; }
        void addFirst(std::shared_ptr<Node> node);
        void addSecond(std::shared_ptr<Node> node);
        std::shared_ptr<Node> getFirst() { return _first; }
        std::shared_ptr<Node> getSecond() { return _second; }

        std::shared_ptr<Path> get_shared_this() { return shared_from_this(); }

    private:
        float _length;
        std::shared_ptr<Node> _first;
        std::shared_ptr<Node> _second;
};

#endif