#pragma once
#include<eigen3/Eigen/Eigen>
#include<vector>
#include"Triangle.h"

class Rasterizer{
public:
    Rasterizer(int w, int h);

    void SetModelTransformation();
    void SetViewTransformation(Eigen::Vector3f eye_pos, Eigen::Vector3f eye_direction = Eigen::Vector3f{0, 0, 0});
    void SetPerspectiveTransformation(float fov, float aspect_ratio, float z_near, float z_far, bool is_perspective = true);
    void SetViewportTransformation(float viewport_width, float viewport_height);

    void SetDepthBuffer(const Triangle& triangle);
private:
    Eigen::Matrix4f model_transform;
    Eigen::Matrix4f view_transform;
    Eigen::Matrix4f perspective_transform;
    Eigen::Matrix4f viewport_transform;

    int width;
    int height;
    std::vector<float> depth_buffer;
    std::vector<Eigen::Vector3f> frame_buffer;
};