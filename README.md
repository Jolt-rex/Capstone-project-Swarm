# CPPND: Capstone Project - Swarm Simulation

This is the final project for the course in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 

Swarm is a tower defence simulation, where enemies spawn at multiple spawn points around the map, and use the A* algorithm to plan their way to
the goal node (pink). The enemies appear as red circles. The user can place towers at any location on the map which will launch missiles towards
the enemies to kill them. A launched missile will follow the enemy until it hits. One missile will kill one enemy. Once all enemies are killed
the simulation ends. If an enemy reaches the goal the simulation ends.

To place a tower, click on the 'T' button to enter Tower Build mode. The left click on the map where you want to place a tower.

## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./swarm`.

## Project Rubric

1. The submission must compile and run.
  * The repository has been cloned from GitHub and compiled using cmake and make. The code executable was able to be run.

2. Loops, Functions, I/O
  * The project contains several exampls of control structures, including for and while loops, and lambda functions.
  * An xml file is parsed using the pugixml library, which is used to construct the vector of node objects and determine spawn points.
  * The project uses the open cv library to handle mouse input, to construct towers as the co-ordinates of the mouse pointer.

3. Object Oriented Programming
  * The project is organised into classes, with methods and members to perform tasks.
  * Data members are protected by using appropiate access specifiers.
  * The Node, Enemy, Tower and Missile classes inherit from the Entity class, and use an initializer list to construct the base class.
  * Classes are documented, with useful member and function name conventions to improve code clarity.
  * Classes encapsulate relevant behaviour and state, with getter and setter functions used.

4. Memory Management
  * References are used in function declarations where possible.
  * The objects Enemy and Missile are moved by their unique pointer to the Model object.
  * Destructors are called to ensure completion of threads.
  * Scope used in conjuction with smart pointers to ensure automatic destruction of dynamic memory.
  * Smart pointers used: unique_ptr, shared_ptr and weak_ptr.

5. Concurrency
  * Multithreading has been used in the program's execution.
  * Mutex's and locks have been used to prevent data races between multiple threads in the program.

## Acknowldgement

This project is based on several projects from the C++ Nano degree program to implement the A* search algorithm and using the opencv library.