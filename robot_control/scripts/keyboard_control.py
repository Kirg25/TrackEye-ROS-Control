#!/usr/bin/env python3
import rospy
from std_msgs.msg import String
from pynput import keyboard

def on_press(key):
    try:
        k = key.char.lower()
        if k == 'f':
            pub.publish("F")
            rospy.loginfo("Sent: F (Forward)")
        elif k == 's':
            pub.publish("S")
            rospy.loginfo("Sent: S (Stop)")
        elif k == 'e':
            pub.publish("EXTEND")
            rospy.loginfo("Sent: EXTEND (5s)")
        elif k == 'r':
            pub.publish("RETRACT")
            rospy.loginfo("Sent: RETRACT (5s)")
        elif k == 'q':
            pub.publish("S")
            pub.publish("STOP_LINEAR")
            rospy.loginfo("Sent: STOP + STOP_LINEAR (Quit)")
            rospy.signal_shutdown("Quit")
            return False
    except AttributeError:
        pass

def on_release(key):
    
    pass

if __name__ == "__main__":
    rospy.init_node('keyboard_motor_control', anonymous=True)
    pub = rospy.Publisher('motor_command', String, queue_size=10)

    print("\nControls:")
    print("  F = Forward")
    print("  S = Stop")
    print("  E = Extend (5 seconds)")
    print("  R = Retract (5 seconds)")
    print("  Q = Quit")

    with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
        listener.join()

