cmake_minimum_required(VERSION 3.5)

project(Robot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
set(OpenCV_DIR E:/opencv/OpenCV-MinGW-Build-OpenCV-4.5.2-x64)
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
 
# Add OpenCV headers location to your include paths
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SOURCES ./img/*.h ./img/*.cpp)
 
# Declare the executable target built from your sources
# add_executable(main main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
 
# Link your application with OpenCV libraries
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
