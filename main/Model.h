#pragma once
#include<eigen3/Eigen/Eigen>
#include<vector>
#include<fstream>
#include<iostream>
#include"TGA.h"

class Model {
public:
	Model(const char* file);
	std::vector<Eigen::Vector3f> vertex;
	std::vector<Eigen::Vector3i> face;
	std::vector<Eigen::Vector3f> texture;
	std::vector<Eigen::Vector3i> face_texture;
	std::vector<Eigen::Vector3f> normal;
	std::vector<Eigen::Vector3i> face_normal;
};
