
#include <stdio.h>
#include <stdlib.h>
#include <ros/ros.h>
#include "std_msgs/String.h"
#include <sensor_msgs/image_encodings.h> 
//#include "ros/xmlrpc_manager.h"

int main( int argc, char **argv)
{
	 int argc1 = 0;
  char** argv1 = NULL;

  //  putenv("ROS_MASTER_URI=http://localhost:11311");
  //	ros::XMLRPCManager::instance();

	ros::init(argc, argv, "hello");
    ros::NodeHandle nh;
    ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10);
     /**
          78    * A count of how many messages we have sent. This is used to create
          79    * a unique string for each message.
          80    */
       int count = 0;
       while (ros::ok())
           {
                 /**
                    85      * This is a message object. You stuff it with data, and then publish it.
                    86      */
                 std_msgs::String msg;
            
                 std::stringstream ss;
                 ss << "hello world " << count;
                 msg.data = ss.str();
            
                 ROS_INFO("%s", msg.data.c_str());
            
                 /**
                    96      * The publish() function is how you send messages. The parameter
                    97      * is the message object. The type of this object must agree with the type
                    98      * given as a template parameter to the advertise<>() call, as was done
                    99      * in the constructor above.
                    100      */
                 chatter_pub.publish(msg);
            
                 ros::spinOnce();
            
                 loop_rate.sleep();
                 ++count;
               }
    
    
       return 0;
    
 
}
