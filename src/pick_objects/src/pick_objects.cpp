#include <ros/ros.h>
#include <tf/tf.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send target requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal target;

  // set up the frame parameters
  target.target_pose.header.frame_id = "map";
  target.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  float goals[2][3] = { {0.35, -1.50, 0.50}, {0.35, -0.5, 0.50}  };

  for (int i=0; i < 2; i++){

      target.target_pose.pose.position.x = goals[i][0];
      target.target_pose.pose.position.y = goals[i][1];
      target.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(goals[i][2]);

      ROS_INFO("Sending target");
      ac.sendGoal(target);

      ac.waitForResult();

      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Target reached!");
      else
        ROS_INFO("Target failed!");
      ros::Duration(5.0).sleep();
  }

  return 0;
}