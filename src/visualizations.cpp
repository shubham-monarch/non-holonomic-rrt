#include <non-holonomic-prm-planner/visualizations.h>
#include <non-holonomic-prm-planner/simple_prm.h>
#include <non-holonomic-prm-planner/constants.h>


#include <geometry_msgs/PoseStamped.h>
#include <tf2/LinearMath/Quaternion.h>
#include <geometry_msgs/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include <geometry_msgs/PoseArray.h>

PRM::Visualize::Visualize(){

    sampled_pts_pub_ = nh_.advertise<geometry_msgs::PoseArray>("sampled_points",   1, true);
    
    ROS_WARN("Inside Visualize Constrcutor!");


}

void PRM::Visualize::visualizeSampledPoints(const std::vector<Node> &nodes_) {

    geometry_msgs::PoseArray pose_array_;

    pose_array_.header.frame_id = "map" ;

    pose_array_.poses.clear();  
    
    int i = 0 ; 
    for(const auto &node_ : nodes_){

        geometry_msgs::Pose world_pose_; 

        float wx_, wy_; 
        const int mx_ = node_.x_; 
        const int my_ = node_.y_;

        Helper::mapToWorld(mx_, my_, wx_, wy_);
        
        
        tf2::Quaternion tf_quat;
        geometry_msgs::Quaternion ros_quat;

        tf_quat.setRPY(0, 0, node_.theta_);

        tf2::convert(tf_quat, ros_quat);

        
        world_pose_.orientation = ros_quat;
        world_pose_.position.x = wx_;
        world_pose_.position.y = wy_;

        pose_array_.poses.push_back(world_pose_);

        //i++; 
        //ROS_INFO("i: %d", i);

    }

    pose_array_.header.stamp = ros::Time::now();

    ROS_INFO("pose_array_.poses.size(): %d", pose_array_.poses.size());

    ROS_DEBUG("Publishing sampled points!");
    
    sampled_pts_pub_.publish(pose_array_);

    
}