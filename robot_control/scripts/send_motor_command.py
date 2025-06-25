#!/usr/bin/env python3
import rospy
from std_msgs.msg import String
import sys

def send_command():
    rospy.init_node('motor_command_publisher', anonymous=True)
    pub = rospy.Publisher('motor_command', String, queue_size=10)
    rate = rospy.Rate(1)  # 1 Hz

    while not rospy.is_shutdown():
        cmd = input("Enter command (F=Forward, S=Stop, Q=Quit): ").strip().upper()
        if cmd == "Q":
            print("Quitting...")
            pub.publish("S")  # Send stop command before quitting
            rospy.signal_shutdown("User requested quit")
            sys.exit(0)
        elif cmd in ["F", "S"]:
            pub.publish(cmd)
            rospy.loginfo(f"Sent command: {cmd}")
        else:
            print("Invalid command. Use 'F' for forward, 'S' for stop, or 'Q' to quit.")

if __name__ == "__main__":
    try:
        send_command()
    except rospy.ROSInterruptException:
        pass
