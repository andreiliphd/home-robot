#!/bin/sh

# Build the catkin_ws
cd $(pwd)/../..

# Launch the nodes
xterm  -e "source devel/setup.bash; export TURTLEBOT_GAZEBO_WORLD_FILE="$(pwd)/src/maps/final.world"; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 7
xterm  -e "source devel/setup.bash; export TURTLEBOT_GAZEBO_MAP_FILE="$(pwd)/src/maps/final_map.yaml"; roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 5
xterm  -e "source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm  -e "source devel/setup.bash; rosrun add_markers add_markers"
