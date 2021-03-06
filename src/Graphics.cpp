#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "Graphics.h"
#include "Model.h"
#include "Node.h"


Graphics::Graphics(std::string mapName, std::shared_ptr<Model> model)
{
    _mapName = mapName;
    _model = model;
}

Graphics::~Graphics()
{
    _thread.join();
}

void Graphics::simulate()
{
    _thread = std::thread(&Graphics::runGUI, this);
}

void Graphics::runGUI() 
{
    std::cout << "Running simulation" << std::endl;
    this->loadBackgroundImage();
    
    cv::setMouseCallback(_windowName, mouseHandler, this);
    _mouseState = kDeselected;
    
    // rendering loop
    while(_model->getGameState() == GameState::kRunning) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        this->renderFrame();
    }
}

// wrapper around the opencv mouse event handler so we can handle it with this object
void Graphics::mouseHandler(int event, int x, int y, int, void* userdata)
{
    if(userdata != nullptr)
    {
        Graphics *graphics = reinterpret_cast<Graphics*>(userdata);
        graphics->graphicsMouseHandler(event, x, y);
    }
}

void Graphics::graphicsMouseHandler(int event, int x, int y)
{
    if(event == cv::EVENT_LBUTTONDOWN) 
    {
        // std::cout << "Mouse location: X:" << x << " Y:" << y << std::endl;

        // if we click inside the T button
        // select towerBuild mode, or deselect if we are already in towerBuild mode
        if((x > 0 && x <= 50) && (y >= 120 && y <= 170))
        {
            _mouseState = (_mouseState == kTowerBuild ? kDeselected : kTowerBuild);
            return;
        }
        
        // if we click somewhere else and are in tower building option
        if(_mouseState == kTowerBuild) 
        {
            int funds = _model->getFunds();
            if(funds >= 100)
            {
                // directly construct the tower on the game model
                int towerId = _model->_towers.size() + 1;
                _model->_towers.emplace_back(std::make_unique<Tower>(towerId, x, y, 150, _model));
                _model->setFunds(funds - 100);
            }
        }
    }
    // right mouse button to deselect
    if(event == cv::EVENT_RBUTTONDOWN) 
    {
        _mouseState = kDeselected;
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
        if(node->isGoal() || node->isSpawnPoint())
        {
            int id = node->getId();
            int x = node->getX();
            int y = node->getY();

            // if it is the goal node, render a pink circle
            if(node->isGoal()) {
                cv::circle(_imageStack[1], cv::Point2d(x, y), 5, cv::Scalar(255, 0, 255), -1);
            }
            // render a red circle for a spawn point
            else if(node->isSpawnPoint()) {
                cv::circle(_imageStack[1], cv::Point2d(x, y), 5, cv::Scalar(0, 0, 255), -1);
            }
        }
    }

    // DRAW PATHS
    // for each node in the model, iterate over it's connected nodes and draw a line between the two
    // uncomment if you wish to see the paths used by the enemies
    // for(const auto &node : _model->getNodes()) {
    //     for(const auto &connectedNode : node->getConnected())
    //     {
    //         cv::line(_imageStack[1], cv::Point2d(node->getX(), node->getY()), cv::Point2d(connectedNode->getX(), connectedNode->getY()), cv::Scalar(0, 255, 0), 1, cv::LINE_4);
    //     }
    // }

    // draw towers
    for(const auto &tower : _model->_towers)
    {
        if(tower)
        {
            int x = tower->getX();
            int y = tower->getY();
            // tower object
            cv::rectangle(_imageStack[1], cv::Point2d(x - 6, y - 2), cv::Point2d(x + 6, y + 2), cv::Scalar(255, 0, 0), cv::FILLED, cv::LINE_4, 0);
            // range circle
            cv::circle(_imageStack[1], cv::Point2d(x, y), _model->_gameRules.towerRange, cv::Scalar(0, 0, 0), 1);
        }
    }

    // draw enemies
    for(const auto &enemy : _model->_enemies)
    {
        if(enemy)
        {
            // enemy is a red, 4px circle
            cv::circle(_imageStack[1], cv::Point2d(enemy->getX(), enemy->getY()), 4, cv::Scalar(0, 0, 255), -1);
        }
    }

    // draw missiles
    for(const auto &missile : _model->_missiles)
    {
        if(missile)
        {
            // missile is a orange, 2px circle
            cv::circle(_imageStack[1], cv::Point2d(missile->getX(), missile->getY()), 2, cv::Scalar(0, 154 ,255), -1);
        }
    }

    // draw controll box
    cv::rectangle(_imageStack[1], cv::Point2d(0, 0), cv::Point2d(170, 120), cv::Scalar(0, 0, 0), cv::FILLED);

    // tower button background and text
    cv::rectangle(_imageStack[1], cv::Point2d(0, 120), cv::Point2d(50, 170), (_mouseState == kDeselected ? cv::Scalar(20, 20, 20) : cv::Scalar(0, 255, 0)), cv::FILLED);
    cv::putText(_imageStack[1], "T", cv::Point2d(15, 155), cv::FONT_HERSHEY_PLAIN, 2, (_mouseState == kDeselected ? cv::Scalar(255, 255, 255) : cv::Scalar(0, 0, 0)), 2);
    
    // draw text
    cv::putText(_imageStack[1], "Funds: " + std::to_string(_model->getFunds()), cv::Point2d(5, 20), cv::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(0, 255, 0), 2);
    cv::putText(_imageStack[1], "Enemies: " + std::to_string(_model->_enemies.size()), cv::Point2d(5, 45), cv::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(0, 255, 0), 2);
    cv::putText(_imageStack[1], "Kills: " + std::to_string(_model->getKills()), cv::Point2d(5, 70), cv::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(0, 255, 0), 2);
    cv::putText(_imageStack[1], "Towers: " + std::to_string(_model->_towers.size()), cv::Point2d(5, 95), cv::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(0, 255, 0), 2);
    cv::putText(_imageStack[1], "Missiles: " + std::to_string(_model->_missiles.size()), cv::Point2d(5, 120), cv::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(0, 255, 0), 2);

    // display the background and overlay image
    float opacity = 0.85;
    cv::addWeighted(_imageStack[1], opacity, _imageStack[0], 1.0 - opacity, 0, _imageStack[2]);
    cv::imshow(_windowName, _imageStack[2]);

    cv::waitKey(33);
}
