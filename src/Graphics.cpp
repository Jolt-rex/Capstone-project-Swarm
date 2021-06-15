#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "Graphics.h"
#include "Intersection.h"

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

    // create entities to be overlaid from _model data
    for(const auto &intersection : _model->getIntersections()) {
        int id = intersection->getId();
        int x = intersection->getX();
        int y = intersection->getY();

        std::cout << "Entity id= " << id << " x= " << x << " y= " << y << std::endl;

        // if it is the goal intersection, render a pink circle
        if(intersection->isGoal()) {
            cv::circle(_imageStack[1], cv::Point2d(x, y), 5, cv::Scalar(219, 3, 252), -1);
        }
        // render a red circle for a spawn point
        else if(intersection->isSpawnPoint()) {
            cv::circle(_imageStack[1], cv::Point2d(x, y), 5, cv::Scalar(0, 0, 255), -1);
        } else {
        // render a green circle for an intersection
            cv::circle(_imageStack[1], cv::Point2d(x, y), 5, cv::Scalar(0, 255, 0), -1);
        }
    }

    std::cout << "Path size: " << _model->getPaths().size() << std::endl;
    for(const auto &path : _model->getPaths()) {
        std::shared_ptr<Intersection> first = path->getFirst();
        std::shared_ptr<Intersection> second = path->getSecond();

        std::cout << "Point from " << first->getX() << " " << first->getY() << " to " << second->getX() << " " << second->getY() << std::endl;

        cv::line(_imageStack[1], cv::Point2d(first->getX(), first->getY()), cv::Point2d(second->getX(), second->getY()), cv::Scalar(0, 255, 0), 1, cv::LINE_4);
    }


    // display the background and overlay image
    float opacity = 0.85;
    cv::addWeighted(_imageStack[1], opacity, _imageStack[0], 1.0 - opacity, 0, _imageStack[2]);
    cv::imshow(_windowName, _imageStack[2]);

    cv::setMouseCallback(_windowName, mouseHandler, NULL);

    cv::waitKey(0);
}
