cmake_minimum_required(VERSION 2.8.3)
project(image_publisher)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

#message(PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR} )
#message(CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR} )

#set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
  cv_bridge
  image_transport
  rviz
)
###################################
## OPENCV                        ##
###################################
set(OpenCV_DIR ~/Libs/opencv/build)
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

if(CMAKE_VERSION VERSION_LESS "2.8.11")
  include_directories(${OpenCV_INCLUDE_DIRS})
endif()

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp std_msgs sensor_msgs rviz cv_bridge
  DEPENDS
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${MAPPING_INCLUDE_DIRS}
)
link_directories(${catkin_LIBRARIES} ${MAPPING_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(image_publisher src/image_publisher.cpp)

add_dependencies(image_publisher ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(image_publisher
   ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

