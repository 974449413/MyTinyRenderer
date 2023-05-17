#pragma once
#include<eigen3/Eigen/Eigen>
#include<vector>
#include"Triangle.h"

class Rasterizer{
public:
    Rasterizer(int h, int w);

    void SetModelTransformation();
    void SetViewTransformation(Eigen::Vector3f eye_pos, Eigen::Vector3f eye_direction = Eigen::Vector3f{0, 0, 0});
    void SetPerspectiveTransformation(float fov, float aspect_ratio, float z_near, float z_far, bool is_perspective = true);
    void SetViewportTransformation(float viewport_height, float viewport_width);

    void SetDepthBuffer(const Triangle& triangle);

    std::vector<Eigen::Vector3f>& GetFrameBuffer() {
        return frame_buffer;
    };
public:
    void DrawLine(Eigen::Vector2i begin, Eigen::Vector2i end);
    void draw_line2(Eigen::Vector3f begin, Eigen::Vector3f end);
private:
    Eigen::Matrix4f model_transform;
    Eigen::Matrix4f view_transform;
    Eigen::Matrix4f perspective_transform;
    Eigen::Matrix4f viewport_transform;

    int GetBufferIndex(int x, int y);

    int width;
    int height;
    std::vector<float> depth_buffer;
    std::vector<Eigen::Vector3f> frame_buffer;
};
