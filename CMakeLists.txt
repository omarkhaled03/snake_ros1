cmake_minimum_required(VERSION 3.0.2)
project(snake_ros1)
find_package(gazebo REQUIRED) 
find_package(controller_manager REQUIRED)
find_package(controller_interface REQUIRED)
find_package(catkin REQUIRED COMPONENTS
    gazebo_plugins
    gazebo_ros
    roscpp
    message_generation
)
add_message_files(
    FILES
    jointcon.msg
)

generate_messages(
    DEPENDENCIES
    std_msgs
    roscpp
)
include_directories(include
    ${catkin_INCLUDE_DIRS}
)
include_directories(
    ${catkin_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/include # for include in package 
${catkin_INCLUDE_DIRS}# for include in build
${GAZEBO_INCLUDE_DIRS} # for Gazebo
${catkin_INCLUDE_DIRS}/../devel/include
)

add_executable(talker
    Script/publish.cpp
)
target_link_libraries( talker
    ${catkin_LIBRARIES}
    ${Boost_LIBRARIES}
)
include_directories(${controller_manager_INCLUDE_DIRS})
include_directories(${controller_interface_INCLUDE_DIRS})      
link_directories(${GAZEBO_LIBRARY_DIRS})               
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(joint_plugin SHARED src/joint_plugin.cpp)
target_link_libraries(joint_plugin ${GAZEBO_LIBRARIES})
