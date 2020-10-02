# Home Robot
============

Robot which is capable of "delivring" packages.
---

## Setup
### Requirements
* Ubuntu 16.04 OS with default make (>=4.1) and g++/gcc (>=5.4) packages
* Gazebo >= 7.0
* ROS Kinetic

### Build Instructions

1. Clone this repo.
2. Execute `catkin_make` from root of repository.
3. Launch one of the scripts from src/scripts.

---

## Explanation
add_marker - Adds and deletes markers.
pick_objects - Navigation to a destination using move_base ROS package.

Used packages:
gmapping - SLAM algorithm implementation for localization and mapping.
turtlebot_teleop - manual operation of a robot.
turtlebot_rviz_launchers - RViz launcher.
turtlebot_gazebo - Turtlebot robot adapted for Gazebo enviroment.

