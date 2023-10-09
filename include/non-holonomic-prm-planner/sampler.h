#ifndef SAMPLER_H
#define SAMPLER_H

#include <unordered_set>
#include <vector>

#include <non-holonomic-prm-planner/ds.h>

#include <geometry_msgs/PoseArray.h>    

#include <geometry_msgs/PolygonStamped.h>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

namespace bg = boost::geometry;
typedef bg::model::d2::point_xy<double> Point_;
typedef bg::model::polygon<Point_> Polygon;

namespace PRM
{

    class Sampler
    {
        public: 

            Sampler(const std::string sampled_points_topic);

            //std::vector<Node2d> generate2DSamplePoints();
            //void sampledPointsCallback(geometry_msgs::PoseArrayPtr msg);

            //bool is_ready = false;

            std::vector<Node2d> samplePointsForRowTransition(  const geometry_msgs::PoseStamped &start, 
                                                const geometry_msgs::PoseStamped &goal,
                                                 const int num_points);

            std::vector<Node2d> gaussianSamplePointsForRowTransition(  const geometry_msgs::PoseStamped &start, 
                                                const geometry_msgs::PoseStamped &goal,
                                                 const int num_points);            

            float getCorrectDirection(const Point mid_, const float theta, const float  sz = 0.1) const; 


            std::vector<Node2d> uniformSampleInRange(const std::vector<float> &range_x, const std::vector<float> &range_y, \
                                                    int num_points);

            //runway sampling
            std::vector<Node2d>  uniformSamplingForRunway(const geometry_msgs::PoseStamped &start, 
                                                const geometry_msgs::PoseStamped &goal,
                                                 const int num_points);

            // section sampling
            std::vector<Node2d> gaussianSampleBetweenWhiteAndGreenpolygons(const geometry_msgs::PoseStamped &start, 
                                                const geometry_msgs::PoseStamped &goal,
                                                 const int num_points);


            std::vector<Node2d> gaussianSampleAlongWhitePolygon(const geometry_msgs::PoseStamped &start, 
                                                const geometry_msgs::PoseStamped &goal,
                                                 const int num_points);


            std::vector<Node2d> uniformSample(const geometry_msgs::PoseStamped &start, 
                                                const geometry_msgs::PoseStamped &goal,
                                                 const int num_points);

            bool getLowestPoint(const geometry_msgs::PoseStamped &start_, const geometry_msgs::PoseStamped &goal, \
                                const geometry_msgs::PoseStamped target_pose, geometry_msgs::PoseStamped &lowest_pose);


            // geometry functions
            void getRunwayPolygon(const geometry_msgs::PoseStamped &start_pose_, const geometry_msgs::PoseStamped &goal_pose_, \
                                const bool start_);

        private: 

            std::unordered_set<Node2d, Node2dHash> sampled_points_; 
            
            ros::Subscriber sampled_points_sub_;
            ros::NodeHandle nh_; 
            const std::string sampled_points_topic_;
            ros::Publisher lowest_pose_pub;
            ros::Publisher current_polygon_pub;
            //ros::Publisher shifted_pose_;
          
    };


};






#endif