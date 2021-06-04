#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <memory>

#include "Entity.h"
#include <opencv2/core.hpp>

class Graphics
{
    public:
        //constructor / destructor

        // getters / setters
        void setBackgroundImage(std::string filename) { _backgroundImage = filename; }
        void setEntities(std::vector<std::shared_ptr<Entity>> &entities) { _entities = entities; }

        void simulate();
        void loadBackgroundImage();

    private:
        std::vector<std::shared_ptr<Entity>> _entities;
        std::string _backgroundImage;
        std::string _windowName;
};

#endif