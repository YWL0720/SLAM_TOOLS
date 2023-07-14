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
#include <geometry_msgs/PoseArray.h>
#include <csignal>

geometry_msgs::PoseArray::ConstPtr last_array;
std::vector<double> vTimes;
std::fstream f;


void SigHandle(int sig)
{
    for (int i = 0; i < last_array->poses.size(); i++)
    {
        geometry_msgs::Point position;
        position = last_array->poses[i].position;
        geometry_msgs::Quaternion orientation;
        orientation = last_array->poses[i].orientation;
        double time = vTimes[i];
        f << time << " " << position.x << " " << position.y << " " << position.z << " " << orientation.x <<
          " " << orientation.y << " " << orientation.z << " " << orientation.w << std::endl;
    }
    f.close();
    ROS_INFO("FINISH");
    ros::shutdown();
}

void addToQueueCallback(const geometry_msgs::PoseArray::ConstPtr & msg)
{
    last_array = msg;
    vTimes.push_back(last_array->header.stamp.toSec());
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pose_listener");
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
        topicName = "/kf_pose";

    if (topicName.empty())
    {
        ROS_ERROR("Given a wrong topic name");
        ros::shutdown();
        return -1;
    }

    ROS_INFO("Listening to %s", topicName.c_str());
    myListener = nh.subscribe<geometry_msgs::PoseArray>(topicName, 100, addToQueueCallback);

    ros::spin();
}


