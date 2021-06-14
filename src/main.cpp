#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Model.h"
#include "Graphics.h"

// Main function entry point
int main(int argc, char** argv) {
    // if(argc != 2) {
    //     std::cout << "Please add a valid map to use" << std::endl;
    //     std::cout << "Options are Brisbane" << std::endl;
    //     return 0;
    // }    

    // load entities from xml file into entities vector of shared ptrs
    Model model = Model("brisbane");

    std::unique_ptr<Graphics> graphics = std::make_unique<Graphics>();

    graphics->setMapName("brisbane");
    graphics->simulate();

    return 0;
}