#include <iostream>
#include <memory>
#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "Graphics.h"
#include "Model.h"
#include "Node.h"

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
    
    cv::setMouseCallback(_windowName, mouseHandler, NULL);
    
    // rendering loop
    while(true) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        this->renderFrame();
    }
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

    // create node entities to be overlaid from _model data
    for(const auto &node : _model->getNodes()) {
        int id = node->getId();
        int x = node->getX();
        int y = node->getY();

        //std::cout << "Entity id= " << id << " x= " << x << " y= " << y << std::endl;

        // if it is the goal node, render a pink circle
        if(node->isGoal()) {
            cv::circle(_imageStack[1], cv::Point2d(x, y), 5, cv::Scalar(255, 0, 255), -1);
        }
        // render a red circle for a spawn point
        else if(node->isSpawnPoint()) {
            cv::circle(_imageStack[1], cv::Point2d(x, y), 5, cv::Scalar(0, 0, 255), -1);
        } else {
        // render a green circle for an node
            cv::circle(_imageStack[1], cv::Point2d(x, y), 5, cv::Scalar(0, 255, 0), -1);
        }
    }

    // for each node in the model, iterate over it's connected nodes and draw a line between the two
    for(const auto &node : _model->getNodes()) {
        for(const auto &connectedNode : node->getConnected())
        {
            cv::line(_imageStack[1], cv::Point2d(node->getX(), node->getY()), cv::Point2d(connectedNode->getX(), connectedNode->getY()), cv::Scalar(0, 255, 0), 1, cv::LINE_4);
        }
    }

    // draw enemies
    for(const auto &enemy : _model->_enemies)
    {
        cv::circle(_imageStack[1], cv::Point2d(enemy->getX(), enemy->getY()), 4, cv::Scalar(255, 0, 0), -1);
    }

    // display the background and overlay image
    float opacity = 0.85;
    cv::addWeighted(_imageStack[1], opacity, _imageStack[0], 1.0 - opacity, 0, _imageStack[2]);
    cv::imshow(_windowName, _imageStack[2]);

    cv::waitKey(0);
}
