#!/usr/bin/env python3
import rospy
from std_msgs.msg import String
from pynput import keyboard

def on_press(key):
    try:
        k = key.char.upper()
        if k == 'F':   # forward while holding F
            pub.publish("F")
            rospy.loginfo("Sent command: F (Forward)")
        elif k == 'R': # reverse while holding R
            pub.publish("R")
            rospy.loginfo("Sent command: R (Reverse)")
    except AttributeError:
        pass

def on_release(key):
    try:
        k = key.char.upper()
        if k in ['F', 'R']:  # stop when released
            pub.publish("S")
            rospy.loginfo("Sent command: S (Stop)")
    except AttributeError:
        pass

    if key == keyboard.Key.esc:
        # ESC key to quit program
        rospy.loginfo("Exiting teleop...")
        return False

if __name__ == "__main__":
    rospy.init_node('keyboard_motor_control_hold', anonymous=True)
    pub = rospy.Publisher('motor_command', String, queue_size=10)

    print("Hold F to move forward, R to reverse, release to stop, ESC to quit.")

    with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
        listener.join()

