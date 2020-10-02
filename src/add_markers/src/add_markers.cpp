#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <tf/tf.h>
#include <math.h>

float odom_x = 0.0, odom_y = 0.0;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  ::odom_x = msg->pose.pose.position.x;
  ::odom_y = msg->pose.pose.position.y;
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(20);
  ros::Subscriber obom_sub = n.subscribe("/odom", 1000, odomCallback);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  uint32_t shape = visualization_msgs::Marker::SPHERE;
  float goals[2][3] = { {0.35, -1.50, 0.50}, {0.35, -0.5, 0.50}  };

  bool reached_pick_up = false;
  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();


  marker.ns = "add_markers";
  marker.id = 0;

  marker.type = shape;

  marker.action = visualization_msgs::Marker::ADD;

  marker.pose.position.x = goals[0][0];
  marker.pose.position.y = goals[0][1];
  marker.pose.position.z = 0.5;
  marker.pose.orientation = tf::createQuaternionMsgFromYaw(goals[0][2]);


  marker.scale.x = 1.0;
  marker.scale.y = 1.0;
  marker.scale.z = 1.0;

  marker.color.r = 0.0f;
  marker.color.g = 0.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();

  while (ros::ok())
  {
    ROS_WARN_ONCE("Executing add_marker!");

    float x_distance, y_distance;

    float tolerance = 1.0;

      if (!reached_pick_up)
      {
        marker_pub.publish(marker);
        x_distance = fabs(marker.pose.position.x - odom_x);
        y_distance = fabs(marker.pose.position.y - odom_y);
        ROS_INFO("Distance to the marker: %f, %f", x_distance, y_distance);

        if( (x_distance < tolerance) && (y_distance < tolerance) )
        {
          marker.action = visualization_msgs::Marker::DELETE;
          marker_pub.publish(marker);
          ROS_WARN_ONCE("Delete marker!");
          ros::Duration(0.5).sleep(); 
          reached_pick_up = true;
        }

      }
      else
      {
          marker.action = visualization_msgs::Marker::ADD;
          marker.pose.position.x = goals[1][0];
          marker.pose.position.y = goals[1][1];
          marker.pose.position.z = 0.5;
          marker.pose.orientation = tf::createQuaternionMsgFromYaw(goals[1][2]);
          marker_pub.publish(marker);
          ROS_WARN_ONCE("Drop off marker published!");

      }

    ros::spinOnce();




    r.sleep();

    }
    return 0;
}
