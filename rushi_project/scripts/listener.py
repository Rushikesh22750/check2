#!/usr/bin/env python3

import rospy
from std_msgs.msg import String

def callback(data):
    # This function is called every time a message is received
    rospy.loginfo(f"I heard: {data.data}")

def listener():
    # Initialize the node with a name 'rushi_listener'
    rospy.init_node('rushi_listener', anonymous=True)

    # Create a subscriber to the same topic as the publisher
    rospy.Subscriber('rushi_chatter', String, callback)

    # Keep python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
