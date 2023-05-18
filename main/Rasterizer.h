#pragma once
#include <eigen3/Eigen/Eigen>
#include <algorithm>
#include <vector>
#include <iostream>

class Rasterizer{
public:
	Rasterizer(std::uint16_t height, std::uint16_t width) : width(width),height(height) { 
		frame_buffer.resize(static_cast<size_t>(height) * width, Eigen::Vector3i{0, 0, 0});
	}
public:
	void DrawLine(Eigen::Vector3i begin, Eigen::Vector3i end, Eigen::Vector3i color = Eigen::Vector3i{0, 0, 255});
	int GetIndex(int x,int y);

	const std::vector<Eigen::Vector3i>& FrameBuffer() const { return frame_buffer; }
private:
	std::uint16_t width;
	std::uint16_t height;

	std::vector<Eigen::Vector3i> frame_buffer;
};
