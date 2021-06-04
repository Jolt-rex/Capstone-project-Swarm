#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Graphics.h"

// Main function entry point
int main(int argc, char** argv) {
    // if(argc != 2) {
    //     std::cout << "Please add a valid map to use" << std::endl;
    //     std::cout << "Options are Brisbane" << std::endl;
    //     return 0;
    // }    
      
    //std::unique_ptr<Graphics> graphics = std::make_unique<Graphics>();

    Graphics *graphics = new Graphics();
    graphics->setBackgroundImage("brisbane");
    //graphics->simulate();

    return 0;
}