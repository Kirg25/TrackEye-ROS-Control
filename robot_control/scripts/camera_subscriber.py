#!/usr/bin/env python3

import rospy

from sensor_msgs.mgs import Image

from cv_bridge import CvBridge

import cv2

subscriberNodeName='camera sensor subscriber'

topicName='video topic'

def callbackFunction(message):
    bridgeObject=CvBridge()

    rospy.loginfo("received a video message/frame")

    convertedFrameBackToCV=bridgeObject.imgmsg_to_cv2(message)

    cv2.imshow("camera", convertedFrameBackToCV)

    cv2.waitKey(1)


rospy.init_node(subscriberNodeName, anonymous=True)

rospy.Subscriber(topicName, Image, callbackFunction)

rospy.spin()

cv2.destroyAllWindows()