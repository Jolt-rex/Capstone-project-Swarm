#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <string>

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
        Graphics(std::string mapname, std::shared_ptr<Model> model);
        ~Graphics();

        // getters / setters

        // cv lib event handler
        static void mouseHandler(int event, int x, int y, int, void* userdata);
        void graphicsMouseHandler(int event, int x, int y);
        
        void loadBackgroundImage();
        void renderFrame();

        void simulate();
        void runGUI();
        void runLoop();
        
    private:
        std::shared_ptr<Model> _model;
        MouseState _mouseState;
        
        std::vector<cv::Mat> _imageStack;
        std::string _mapName;
        std::string _windowName;

        std::thread _thread;
        std::mutex _mutex;
};

#endif