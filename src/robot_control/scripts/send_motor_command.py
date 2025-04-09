#!/usr/bin/env python3
import rospy
from std_msgs.msg import String

def send_command():
    rospy.init_node('motor_command_publisher', anonymous=True)
    pub = rospy.Publisher('motor_command', String, queue_size=10)
    rate = rospy.Rate(1)  # 1 Hz

    while not rospy.is_shutdown():
        cmd = input("Enter command (F=Forward, S=Stop): ").strip().upper()
        if cmd in ["F", "S"]:
            pub.publish(cmd)
            rospy.loginfo(f"Sent command: {cmd}")
        else:
            print("Invalid command. Use 'F' for forward or 'S' for stop.")

if __name__ == "__main__":
    try:
        send_command()
    except rospy.ROSInterruptException:
        pass
