cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)
project(Swarm)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -g")

find_package(OpenCV 4.1 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

# Find all executables
file(GLOB project_SRCS src/*.cpp src/libs/*.cpp) #src/*.h

# Add project executable
add_executable(swarm ${project_SRCS})
target_link_libraries(swarm ${OpenCV_LIBRARIES})