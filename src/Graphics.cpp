#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.cpp>

#include "Graphics.h"

void Graphics::simulate() 
{
    std::cout << "Running simulation" << std::endl;

    //this->loadBackgroundImage();
}

void Graphics::loadBackgroundImage()
{
    _windowName = "Swarm - " + _backgroundImage;



}
