# cmake needs this line
cmake_minimum_required(VERSION 3.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# OpenCV build dir
set("OpenCV_DIR" "/mnt/8668734168732F55/Libraries/opencv-4.1.0/build/")

# Define project name
project(opencv_template LANGUAGES CXX)

# Find OpenCV, you may need to set OpenCV_DIR variable
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


# Declare the executable target built from your sources
add_executable(program src/main.cpp src/HandMasker.cpp src/HandMasker.hpp)

# Link your application with OpenCV libraries
target_link_libraries(program
  ${OpenCV_LIBS}
)