#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <memory>

#include "Entity.h"
#include "Model.h"
#include <opencv2/core.hpp>

class Graphics
{
    public:
        //constructor / destructor

        // getters / setters
        void setMapName(std::string mapName) { _mapName = mapName; }
        void setModel(std::shared_ptr<Model> model) { _model = model; }

        void simulate();
        void runLoop();
        void loadBackgroundImage();
        void renderFrame();

    private:
        std::shared_ptr<Model> _model;
        
        // _imageStack elements are: 
        // [0] -> original image
        // [1] -> overlay entities
        // [2] -> [0] and [1] combined for final render to screen
        std::vector<cv::Mat> _imageStack;

        std::string _mapName;
        std::string _windowName;
};

#endif