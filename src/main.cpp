#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>

#include "Model.h"
#include "Graphics.h"
#include "SpawnController.h"

// Main function entry point
int main(int argc, char** argv) {
    // if(argc != 2) {
    //     std::cout << "Please add a valid map to use" << std::endl;
    //     std::cout << "Options are Brisbane" << std::endl;
    //     return 0;
    // }    

    // load entities from xml file into entities vector of shared ptrs
    std::shared_ptr<Model> model = std::make_shared<Model>("brisbane");

    std::unique_ptr<SpawnController> spawnController = std::make_unique<SpawnController>(model);

    std::unique_ptr<Graphics> graphics = std::make_unique<Graphics>();

    graphics->SetMapName("brisbane");
    graphics->SetModel(model);

    std::thread graphicsThread(&Graphics::simulate, graphics.get());

    spawnController->Simulate();

    graphicsThread.join();

    return 0;
}