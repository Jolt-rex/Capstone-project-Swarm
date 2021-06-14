#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "Graphics.h"

void mouseHandler(int event, int x, int y, int, void*)
{
    if(event == cv::EVENT_LBUTTONDOWN) {
        std::cout << "Mouse location: X:" << x << " Y:" << y << std::endl;
    }
}

void Graphics::simulate() 
{
    std::cout << "Running simulation" << std::endl;

    this->loadBackgroundImage();
    this->renderFrame();
}

void Graphics::loadBackgroundImage()
{
    _windowName = "Swarm - " + _mapName;
    cv::namedWindow(_windowName, cv::WINDOW_NORMAL);

    cv::Mat background = cv::imread("../maps/" + _mapName + ".png");
    _imageStack.emplace_back(background);           // original background to re-use with overlay
    _imageStack.emplace_back(background.clone());   // create deep copy of original bg
    _imageStack.emplace_back(background.clone());   // another deep copy of original for final image to be displayed
}

void Graphics::renderFrame() 
{
    // reset elements [1] and [2] to original image
    _imageStack[1] = _imageStack[0].clone();
    _imageStack[2] = _imageStack[0].clone();

    // create entities to be overlaid
    cv::Scalar sc(219, 3, 252);
    cv::circle(_imageStack[1], cv::Point2d(985, 481), 5, sc, -1);

    // create entities to be overlaid from _model data
    for(const auto &entity : _model->getEntities()) {
        std::cout << "Entity id= " << entity->getId() << " x= " << entity->getX() << " y= " << entity->getY() << std::endl;

        // if it is the goal intersection, render a pink circle
        if(entity->getId() == 0) {
            cv::circle(_imageStack[1], cv::Point2d(entity->getX(), entity->getY()), 5, cv::Scalar(219, 3, 252), -1);
            continue;
        }

        cv::circle(_imageStack[1], cv::Point2d(entity->getX(), entity->getY()), 5, cv::Scalar(0, 255, 0), -1);
    }


    // display the background and overlay image
    float opacity = 0.85;
    cv::addWeighted(_imageStack[1], opacity, _imageStack[0], 1.0 - opacity, 0, _imageStack[2]);
    cv::imshow(_windowName, _imageStack[2]);

    cv::setMouseCallback(_windowName, mouseHandler, NULL);

    cv::waitKey(0);
}
