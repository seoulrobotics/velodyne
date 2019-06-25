// Copyright (C) 2009, 2010, 2011, 2012, 2019 Austin Robot Technology, Jack O'Quin, Jesse Vera, Joshua Whitley,
// Sebastian Pütz All rights reserved.
//
// Software License Agreement (BSD License 2.0)
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//  * Neither the name of {copyright_holder} nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

/** @file

    This class transforms raw Velodyne 3D LIDAR packets to PointCloud2
    in the /map frame of reference.

*/

#ifndef VELODYNE_POINTCLOUD_TRANSFORM_H
#define VELODYNE_POINTCLOUD_TRANSFORM_H

#include <memory>
#include <string>

//#include <diagnostic_updater/diagnostic_updater.hpp>
//#include <diagnostic_updater/publisher.hpp>
#include <message_filters/subscriber.h>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/message_filter.h>
#include <tf2_ros/transform_listener.h>

#include <velodyne_msgs/msg/velodyne_scan.hpp>
#include <velodyne_pointcloud/rawdata.h>
#include <velodyne_pointcloud/pointcloudXYZIR.h>

namespace velodyne_pointcloud
{
class Transform : public rclcpp::Node
{
public:
  Transform();
  ~Transform()
  {
  }

private:
  void processScan(const std::shared_ptr<const velodyne_msgs::msg::VelodyneScan> & scanMsg);

  std::shared_ptr<velodyne_rawdata::RawData> data_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr output_;
  std::shared_ptr<tf2_ros::TransformListener> tf_ptr_;
  message_filters::Subscriber<velodyne_msgs::msg::VelodyneScan> velodyne_scan_;
  tf2_ros::Buffer tf_buffer_;
  tf2_ros::MessageFilter<velodyne_msgs::msg::VelodyneScan> tf_filter_;

  /// configuration parameters
  typedef struct
  {
    std::string target_frame;  ///< target frame
    std::string fixed_frame;   ///< fixed frame
    bool organize_cloud;       ///< enable/disable organized cloud structure
    double max_range;          ///< maximum range to publish
    double min_range;          ///< minimum range to publish
    uint16_t num_lasers;       ///< number of lasers
    double view_direction;
    double view_width;
  }
  Config;
  Config config_;

  std::shared_ptr<velodyne_rawdata::DataContainerBase> container_ptr;

  // diagnostics updater
  //diagnostic_updater::Updater diagnostics_;
  double diag_min_freq_;
  double diag_max_freq_;
  //std::shared_ptr<diagnostic_updater::TopicDiagnostic> diag_topic_;
};
}  // namespace velodyne_pointcloud

#endif  // VELODYNE_POINTCLOUD_TRANSFORM_H
