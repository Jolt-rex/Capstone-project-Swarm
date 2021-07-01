#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <memory>
#include <mutex>

#include "Entity.h"
#include "Model.h"
#include <opencv2/core.hpp>

enum MouseState {
    kDeselected, kTowerBuild
};

class Graphics
{
    public:
        //constructor / destructor

        // getters / setters
        void setMapName(std::string mapName) { _mapName = mapName; }
        void setModel(std::shared_ptr<Model> model) { _model = model; }

        // cv lib event handler
        static void mouseHandler(int event, int x, int y, int, void* userdata);
        void graphicsMouseHandler(int event, int x, int y);

        void simulate();
        void runLoop();
        void loadBackgroundImage();
        void renderFrame();

    private:
        std::shared_ptr<Model> _model;

        MouseState _mouseState;
        
        // _imageStack elements are: 
        // [0] -> original image
        // [1] -> overlay entities
        // [2] -> [0] and [1] combined for final render to screen
        std::vector<cv::Mat> _imageStack;

        std::string _mapName;
        std::string _windowName;

        std::mutex _mutex;
};

#endif