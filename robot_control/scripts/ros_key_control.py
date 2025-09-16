#!/usr/bin/env python3
import rospy
from std_msgs.msg import String
from pynput import keyboard

def on_press(key):
    try:
        k = key.char.upper()
        if k == 'F':
            pub.publish("F")
            rospy.loginfo("Sent command: F (Forward)")
        elif k == 'R':
            pub.publish("R")
            rospy.loginfo("Sent command: R (Reverse)")
        elif k == 'S':
            pub.publish("S")
            rospy.loginfo("Sent command: S (Stop)")
        elif k == 'Q':
            pub.publish("S")
            rospy.loginfo("Sent command: S (Stop)")
            rospy.signal_shutdown("User pressed Q to quit.")
            return False
    except AttributeError:
        pass

if __name__ == "__main__":
    rospy.init_node('keyboard_motor_control', anonymous=True)
    pub = rospy.Publisher('motor_command', String, queue_size=10)

    print("Press F = Forward, R = Reverse, S = Stop, Q = Quit.")

    with keyboard.Listener(on_press=on_press) as listener:
        listener.join()
