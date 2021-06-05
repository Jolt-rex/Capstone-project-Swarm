#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "Graphics.h"

void Graphics::simulate() 
{
    std::cout << "Running simulation" << std::endl;

    this->loadBackgroundImage();
}

void Graphics::loadBackgroundImage()
{
    _windowName = "Swarm - " + _mapName;
    cv::namedWindow(_windowName, cv::WINDOW_NORMAL);

    cv::Mat background = cv::imread("../img/" + _mapName + ".png");
    _imageStack.emplace_back(background);

    cv::imshow(_windowName, _imageStack.at(0));

}
