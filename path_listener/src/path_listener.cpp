#include <ros/ros.h>
#include <iostream>
#include <nav_msgs/Path.h>
#include <fstream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/PoseStamped.h>
#include <queue>
#include <std_srvs/Trigger.h>
#include <nav_msgs/Odometry.h>
#include <csignal>

std::queue<nav_msgs::PathConstPtr> qPath;
std::fstream f;


void SigHandle(int sig)
{
    nav_msgs::PathConstPtr path = qPath.back();
    for (auto &pose: path->poses)
    {
        geometry_msgs::Point position;
        position = pose.pose.position;
        geometry_msgs::Quaternion orientation;
        orientation = pose.pose.orientation;
        double time = pose.header.stamp.toSec();
        f << time << " " << position.x << " " << position.y << " " << position.z << " " << orientation.x <<
          " " << orientation.y << " " << orientation.z << " " << orientation.w << std::endl;
    }
    f.close();
    ROS_INFO("FINISH");
    ros::shutdown();
}

void addToQueueCallback(const nav_msgs::PathConstPtr & msg)
{
    qPath.push(msg);
    if (qPath.size()>100)
        qPath.pop();
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "traj_listener");
    ros::NodeHandle nh;
    signal(SIGINT, SigHandle);
    ros::Subscriber myListener;
    nh.setParam("/use_sim_time", true);

    f.open("trajectory.txt", std::ios::out);
    f.precision(9);
    f.setf(std::ios::fixed);

    std::string topicName;
    if (argc > 1)
        topicName = std::string(argv[1]);
    else
        topicName = "/path";

    if (topicName.empty())
    {
        ROS_ERROR("Given a wrong topic name");
        ros::shutdown();
        return -1;
    }

    ROS_INFO("Listening to %s", topicName.c_str());
    myListener = nh.subscribe<nav_msgs::Path>(topicName, 100, addToQueueCallback);

    ros::spin();
}


