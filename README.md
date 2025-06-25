# TrackEye-ROS-Control (Teleop-updated)

An 2025 FYP project by mechatronic student


*-Arduino*:Project_MEC3-25_2Teleop_control

*-Ros*: robot_control


**Running the system**

roscore

rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 _baud:=57600

rosrun robot_control ros_key_control.py




**Troubleshooting** 

Python file not executeable

*chmod +x /home/<User>/catkin_ws/src/robot_control/scripts/send_motor_command.py
