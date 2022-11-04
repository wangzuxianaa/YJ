cmake_minimum_required(VERSION 3.0.2)
project(YJI)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")  
set(CMAKE_CXX_STANDARD 17)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  message_generation
)

find_package(jsoncpp REQUIRED)

find_package(cpr REQUIRED)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

add_message_files(
  FILES
  agv1.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES YJI
  CATKIN_DEPENDS roscpp std_msgs message_runtime
#  DEPENDS system_lib
)

# include(FetchContent)
# FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
#                          GIT_TAG 871ed52d350214a034f6ef8a3b8f51c5ce1bd400) # The commit hash for 1.9.0. Replace with the latest from: https://github.com/libcpr/cpr/releases
# FetchContent_MakeAvailable(cpr)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  # /usr/local/include
)

add_library(${PROJECT_NAME} SHARED
src/System.cc
src/UDPServer.cc
src/Common.cc
src/SystemController.cc
src/MissionPlanner.cc
src/MissionExecutor.cc
)



add_executable(main 
src/main.cc)

target_link_libraries(main PRIVATE ${PROJECT_NAME} ${catkin_LIBRARIES} /usr/local/lib/libjsoncpp.a cpr::cpr)

# target_link_libraries(main  ${PROJECT_NAME})