#pragma once
#include<eigen3/Eigen/Eigen>

Eigen::Matrix4f ModelTransformation();
Eigen::Matrix4f ViewTransformation(Eigen::Vector3f eye_pos, Eigen::Vector3f eye_direction = Eigen::Vector3f{0, 0, 0});
Eigen::Matrix4f PerspectiveTransformation(float fov, float aspect_ratio, float z_near, float z_far, bool is_perspective = true);
Eigen::Matrix4f ViewportTransformation(float viewport_width, float viewport_height);
