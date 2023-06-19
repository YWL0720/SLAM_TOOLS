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