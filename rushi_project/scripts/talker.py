#!/usr/bin/env python3

import rospy
from std_msgs.msg import String

def talker():
    # Initialize the node with a name 'rushi_talker'
    rospy.init_node('rushi_talker', anonymous=True)

    # Create a publisher. 
    # Topic name: 'rushi_chatter'
    # Message type: std_msgs/String
    pub = rospy.Publisher('rushi_chatter', String, queue_size=10)

    # Set a publishing rate in Hz
    rate = rospy.Rate(1)  # 1 message per second

    while not rospy.is_shutdown():
        # The content of the message
        message_str = "Rushi"

        # Log some info
        rospy.loginfo(f"Publishing: {message_str}")

        # Publish the message
        pub.publish(message_str)

        # Sleep to maintain the loop rate
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
