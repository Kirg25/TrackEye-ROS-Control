#!/usr/bin/env python3

import subprocess

# Define your commands
commands = [
    "source /opt/ros/noetic/setup.bash && roscore",
    "source /opt/ros/noetic/setup.bash && source ~/catkin_ws/devel/setup.bash && rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 _baud:=57600",
    "source /opt/ros/noetic/setup.bash && source ~/catkin_ws/devel/setup.bash && rosrun robot_control ros_key_control.py"
]

# Base command
terminal_cmd = ["gnome-terminal"]

# Add each command in a new tab
for i, cmd in enumerate(commands):
    terminal_cmd.extend([
        "--tab",
        "--title=ROS_Tab_{}".format(i + 1),
        "--",
        "bash",
        "-c",
        f"{cmd}; exec bash"
    ])

# Run the full terminal command
subprocess.run(terminal_cmd)
