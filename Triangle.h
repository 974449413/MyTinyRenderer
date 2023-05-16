#pragma once
#include<eigen3/Eigen/Eigen>
#include<array>

typedef struct _TRIANGLE{

    _TRIANGLE();

    std::array<Eigen::Vector3f, 3> vertex;
    std::array<Eigen::Vector3f, 3> color;
    std::array<Eigen::Vector3f, 3> normal_vector;
    std::array<Eigen::Vector3f, 3> uv_coordinate;
}Triangle;