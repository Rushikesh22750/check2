#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <std_msgs/Header.h>
#include <iostream>
#include <vector>

// Custom message for YOLO bounding boxes
#include <swaayatt_rushikesh/DetectedObjects.h>
#include <swaayatt_rushikesh/DetectedObject.h>

// Callback function to process and publish the image
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try
    {
        // Process image data directly from ROS message
        std::vector<uint8_t> image_data = msg->data;

        // Here, you would need to convert the raw data to an OpenCV Mat or another format
        // However, without OpenCV, you would need to manage the image conversion manually
        // Assuming 'image_data' is already in the correct format for processing
        // You can process the raw image data here (like resizing, grayscale, etc.)

        // For example, we can just print the size of the image data:
        ROS_INFO("Received image of size: %zu bytes", image_data.size());

        // To publish the processed image back to ROS, we need to use a regular sensor_msgs::Image
        // Create a new image message for processed image (assuming no actual OpenCV manipulation)
        sensor_msgs::ImagePtr processed_msg(new sensor_msgs::Image());
        processed_msg->header = msg->header; // Same header as the input message
        processed_msg->height = msg->height;
        processed_msg->width = msg->width;
        processed_msg->encoding = msg->encoding; // Same encoding as input image
        processed_msg->step = msg->step;
        processed_msg->data = image_data; // Assume no modification to the raw data

        // Publish the processed image
        static ros::NodeHandle nh;
        static ros::Publisher pub = nh.advertise<sensor_msgs::Image>("/processed_image", 1);
        pub.publish(processed_msg);

        ROS_INFO("Published processed image to /processed_image");

        // Optionally, display the image size
        std::cout << "Processed Image Size: " << processed_msg->data.size() << " bytes" << std::endl;

    }
    catch (const std::exception &e)
    {
        ROS_ERROR("Exception: %s", e.what());
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_subscriber");
    ros::NodeHandle nh;

    // Subscribe to the camera image topic
    ros::Subscriber sub = nh.subscribe("/camera/color/image_raw", 1, imageCallback);

    ros::spin(); // Keep the node running and processing messages
    return 0;
}
