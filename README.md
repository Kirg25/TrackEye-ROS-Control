# TrackEye-ROS-Control
An 2025 FYP project by mechatronic student


-Arduino:robo_car_1 (for motor testing)
	Project_MEC3-25_1
-Ros: robot_control

Running the system

roscore
rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 _baud:=57600
rosrun robot_control send_motor_command.py



#Demo

-Arduino: - Demo_robot.ino
	
	
	
-Ros: - demo_robot_control.py

Running the system

roscore
rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 _baud:=57600

rosrun robot_control demo_robot_control.py
