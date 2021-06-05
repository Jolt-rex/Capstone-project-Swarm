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
        void setMapName(std::string mapName) { _mapName = mapName; }
        void setEntities(std::vector<std::shared_ptr<Entity>> &entities) { _entities = entities; }

        void simulate();
        void loadBackgroundImage();
        void renderFrame();

    private:
        std::vector<std::shared_ptr<Entity>> _entities;

        // _imageStack elements are: 
        // [0] -> original image
        // [1] -> overlay entities
        // [2] -> [0] and [1] combined for final render to screen
        std::vector<cv::Mat> _imageStack;

        std::string _mapName;
        std::string _windowName;
};

#endif