#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(aws-desktop)

add_definitions("-Wall")
add_definitions("-Werror")

# Define sources and executable
set(EXECUTABLE_NAME "aws-desktop")
add_executable(${EXECUTABLE_NAME} MACOSX_BUNDLE
                                  imgui/imgui.cpp
                                  imgui/imgui-SFML.cpp
                                  imgui/imgui_draw.cpp
                                  src/main.cpp
                                  src/settings.cpp
                                  src/imgui_shim.cpp
                                  src/window_manager.cpp
                                  src/cloudformation_window.cpp
                                  src/vpc_visualizer_window.cpp)

# Without this, #include <imgui> won't work.
include_directories("imgui" "inc")

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
  target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
endif()

# AWS SDK
set(aws-sdk-cpp_DIR "/Users/drautb/GitHub/aws/aws-sdk-cpp")
find_package(aws-sdk-cpp REQUIRED)
if (aws-sdk-cpp_FOUND)
  include_directories("${aws-sdk-cpp_DIR}/aws-cpp-sdk-core/include")
  include_directories("${aws-sdk-cpp_DIR}/aws-cpp-sdk-cloudformation/include")
  include_directories("${aws-sdk-cpp_DIR}/aws-cpp-sdk-ec2/include")
  target_link_libraries(${EXECUTABLE_NAME} aws-cpp-sdk-cloudformation
                                           aws-cpp-sdk-ec2)
endif()

target_compile_features(aws-desktop PRIVATE cxx_delegating_constructors)

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
