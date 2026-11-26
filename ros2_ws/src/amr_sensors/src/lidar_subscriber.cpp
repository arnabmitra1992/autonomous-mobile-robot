#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/point_cloud2_iterator.hpp"
#include <cmath>
#include <memory>
#include <vector>
#include <utility>



class LidarSubscriber : public rclcpp::Node
{
public:
    LidarSubscriber() : Node("lidar_subscriber")
    {
        subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan",
            rclcpp::SensorDataQoS(),
            [this](sensor_msgs::msg::LaserScan::SharedPtr msg) {
                this->scanCallback(msg);
            }
        );

    
        pointcloud_publisher_ =
            this->create_publisher<sensor_msgs::msg::PointCloud2>(
                "/obstacle_points",
                rclcpp::SensorDataQoS()
        );
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_publisher_;
    void scanCallback(
        const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        // Get the number of measurements in the scan
        auto num_measurements = msg->ranges.size();
        RCLCPP_INFO(this->get_logger(), 
        "Number of measurements: %zu", 
        num_measurements);

        std::vector<std::pair<float, float>> obstacle_points_local;
        for (std::size_t i = 0; i < num_measurements; i++)
        {
            float range = msg->ranges[i];
            if (!std::isfinite(range) ||
                range < msg->range_min ||
                range > msg->range_max)
            {
                continue; // Skip invalid measurements
            }
            float angle = msg->angle_min + i * msg->angle_increment;
            // Convert polar to cartesian coordinates
            float x = range * std::cos(angle);
            float y = range * std::sin(angle);
            // Insert the coordinate pair into obstacle_points
            obstacle_points_local.push_back(std::make_pair(x, y));
        }
        sensor_msgs::msg::PointCloud2 cloud_msg;
        // Preserve the original timestamp and coordinate frame
        cloud_msg.header = msg->header;
        // Unorganized point cloud
        cloud_msg.height = 1;
        // Number of valid points
        cloud_msg.width = obstacle_points_local.size();
        // Byte ordering
        cloud_msg.is_bigendian = false;
        // All invalid measurements have been filtered
        cloud_msg.is_dense = true;

        // Define fields and allocate memory
        sensor_msgs::PointCloud2Modifier modifier(cloud_msg);
        modifier.setPointCloud2FieldsByString(1, "xyz");
        modifier.resize(obstacle_points_local.size());
        sensor_msgs::PointCloud2Iterator<float> iter_x(cloud_msg, "x");
        sensor_msgs::PointCloud2Iterator<float> iter_y(cloud_msg, "y");
        sensor_msgs::PointCloud2Iterator<float> iter_z(cloud_msg, "z");
        if (!obstacle_points_local.empty())
        {
            for (const auto& point : obstacle_points_local)
            {
           
                *iter_x = point.first;
                *iter_y = point.second;
                *iter_z = 0.0f; // Assuming a 2D LIDAR, z-coordinate is 0
                ++iter_x;
                ++iter_y;
                ++iter_z;
            }
        }
        pointcloud_publisher_->publish(cloud_msg);
        
        RCLCPP_INFO(
            this->get_logger(),
            "Total rays: %zu | Valid points: %zu",
            num_measurements,
            obstacle_points_local.size()
        );     
        
    }
};

int main(int argc, char **argv)
{
    // Initialize ROS 2
    rclcpp::init(argc, argv);
    // Create an instance of LidarSubscriber
    auto node = std::make_shared<LidarSubscriber>();
    // Spin the node
    rclcpp::spin(node);
    // Shutdown ROS 2
    rclcpp::shutdown();
    return 0;
}