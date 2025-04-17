**#Demo**


-Arduino: - Demo_robot.ino
	
	
	
-Ros: - demo_robot_control.py

Running the system

roscore
rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 _baud:=57600

rosrun robot_control demo_robot_control.py
