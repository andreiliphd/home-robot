#!/bin/sh

cd $(pwd)/../..

xterm  -e "source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 10

