# SLAM_TOOLS
ROS工具包集合，更新SLAM实用的ROS工具
- dataset_converter
- path_listener

---

## dataset_converter
可以将ROS bag中的RGBD图像数据转换成TUM数据集的格式，并自动进行深度图和彩色图的匹配生成associate.txt文件
### 使用方法
#### 0 编译及环境
测试环境Ubuntu 20.04 + ROS noetic 
```bash
cp datasert_converter YOUR_WORKSPACE_PATH/src
cd YOUR_WORKSPACE_PATH
catkin_make
```

#### 1 修改rosbagToTUM.launch
指定输出目录，rosbag名称，彩色图话题名称，深度图话题名称
```
<arg name="outputpath" default="PATH_TO_OUTPUT_DIR" />
<param name="bag_name" type="string" value="BAG_NAME" />
<param name="topic_name_rgb" type="string" value="TOPIC_NAME_OF_RGB" />
<param name="topic_name_depth" type="string" value="TOPIC_NAME_OF_DEPTH" />
```
#### 2 终端运行
```bash
roslaunch dataset_converter rosbagToTUM.launch 
```

#### 最终可以获得如下的结构
```
PATH_TO_OUTPUT_DIR
└── dataset
    ├── associate.txt
    ├── depth
    ├── depth.txt
    ├── rgb
    └── rgb.txt
```
---
## path_listener
可以记录nav_msgs/Path类型的消息信息，并将轨迹保存为TUM格式，方便对定位轨迹进行评估
### 使用方法
#### 0 编译及环境
测试环境Ubuntu 20.04 + ROS noetic 
```bash
cp -r path_listener/ YOUR_WORKSPACE_PATH/src
cd YOUR_WORKSPACE_PATH
catkin_make
```
#### 1 指定接收的话题名，运行节点
默认话题名为/path
```bash
rosrun path_listener path_listener YOUR_TOPIC_NAME
```
#### 2 结束记录
Ctrl+C终止即可，最终在运行目录下生成trajectory.txt文件
