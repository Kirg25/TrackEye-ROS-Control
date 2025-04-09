#!/usr/bin/env python

import rospy
from std_msgs.msg import String

def publish_commands():
         rospy.init_node('robot_command_publisher', anonymous=True)
         pub = rospy.Publisher('robot_command', String, queue_size=10)
         rate = rospy.Rate(1)  # 1 Hz

while not rospy.is_shutdown():
             command = input("Enter command (F for forward, S for stop): ").strip().upper()
             if command in ["F", "S"]:
                 pub.publish(command)
                 rospy.loginfo(f"Published command: {command}")
             else:
                 rospy.logwarn("Invalid command. Please enter 'F' or 'S'.")
             rate.sleep()

if __name__ == '__main__':
         try:
             publish_commands()
         except rospy.ROSInterruptException:
             pass
