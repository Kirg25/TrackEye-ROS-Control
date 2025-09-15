#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist

def main():
    rospy.init_node('simple_move_controller')
    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)

    move = Twist()
    stop = Twist()

    print("Send command: F (forward), S (stop), Q (quit)")

    while not rospy.is_shutdown():
        cmd = input("Command: ").strip().upper()

        if cmd == "F":
            move.linear.x = 1.0
            pub.publish(move)
            print("Moving forward...")

        elif cmd == "S":
            stop.linear.x = 0.0
            pub.publish(stop)
            print("Stopped.")

        elif cmd == "Q":
            print("Exiting...")
            break

        else:
            print("Invalid command. Use F, S, or Q.")

if __name__ == "__main__":
    try:
        main()
    except rospy.ROSInterruptException:
        pass
