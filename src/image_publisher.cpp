#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <string.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>

using namespace std;
//namespace enc = sensor_msgs::image_encodings;
using namespace cv;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
//  string path_to_depth;
//  string path_to_rgb;
  image_transport::ImageTransport it_depth(nh);
  image_transport::ImageTransport it_rgb(nh);
  image_transport::Publisher pub_depth = it_depth.advertise("/camera/depth/image_raw", 1);
  image_transport::Publisher pub_rgb = it_rgb.advertise("/camera/rgb/image_raw", 1);
  cv::Mat image_rgb; //= cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
  cv::Mat image_depth; //= cv::imread(ossDepth.str(), CV_LOAD_IMAGE_ANYDEPTH);
  std::string path2sequenceRGB, path2sequenceDepth, path2sequence;

  int seq_num = 4; //change that!

  path2sequence = "/media/mikolajnowaczyk/dysk zewnetrzny/dataset/rgbd_dataset_freiburg3_long_office_household/";
  path2sequence = "/media/mikolajnowaczyk/dysk zewnetrzny/icl/living_room_" + std::to_string(seq_num) + "/";

  path2sequenceRGB = path2sequence + "rgb/";
  path2sequenceDepth = path2sequence + "depth/";

  int start = 0;
  int end = 1240;
//  int limit = 100;
//  switch (seq_num)
//        {
//           case 1:
//              limit = 1508;
//              break;
//           case 2:
//              limit = 965;
//              break;
//           case 3:
//              limit = 880;
//              break;
//           case 4:
//              limit = 1240;
//              break;
//            default:
//              limit = 800;
//        }
  ros::Rate loop_rate(30);
  int i = start;
  while (nh.ok() && (i < end))
  {
      //TUM
//      std::ostringstream ossRGB;  ossRGB.str(std::string());
//      ossRGB << path2sequence << "rgb_" << std::setfill('0') << std::setw(5) << i << ".png";
//      std::ostringstream ossDepth;  ossDepth.str(std::string());
//      ossDepth << path2sequence << "depth_" << std::setfill('0') << std::setw(5) << i << ".png";

      //ICL
      std::ostringstream ossRGB;  ossRGB.str(std::string());
      ossRGB << path2sequenceRGB << i << ".png";
      std::ostringstream ossDepth;  ossDepth.str(std::string());
      ossDepth << path2sequenceDepth << i << ".png";

      cout<<"Debug ossRGB = " << ossRGB.str()<< endl;
      cout<<"Debug ossDepth = " << ossDepth.str()<< endl;

      image_rgb = cv::imread(ossRGB.str(), CV_LOAD_IMAGE_COLOR);
      image_depth = cv::imread(ossDepth.str(), CV_LOAD_IMAGE_ANYDEPTH);

      cout<<"rgb empty? "<<image_rgb.empty()<<endl;
      cout<<"depth empty? "<<image_depth.empty()<<endl;

      //cv::Mat img; // << image MUST be contained here
      cv_bridge::CvImage rgb_bridge, depth_bridge;
      sensor_msgs::Image rgb_msg, depth_msg; // >> message to be sent

      std_msgs::Header header; // empty header
//      header.seq = counter; // user defined counter
      header.stamp = ros::Time::now(); // time
      rgb_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::RGB8, image_rgb);
      depth_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::MONO16, image_depth);

      rgb_bridge.toImageMsg(rgb_msg); // from cv_bridge to sensor_msgs::Image
      depth_bridge.toImageMsg(depth_msg); // from cv_bridge to sensor_msgs::Image

      pub_rgb.publish(rgb_msg);
      pub_depth.publish(depth_msg);

      i++;
      ros::spinOnce();
      loop_rate.sleep();
  }
  cout<<"Seq done"<<endl;
}
