#pragma once
#include <eigen3/Eigen/Eigen>
#include <algorithm>
#include <vector>
#include <iostream>

class Model;

class Rasterizer{
public:
	Rasterizer(std::uint16_t height, std::uint16_t width) : width(width),height(height) { 
		frame_buffer.resize(static_cast<size_t>(height) * width, Eigen::Vector3i{0, 0, 0});
	}
public:
	enum class Primitive{
		Line,
		Triangle
	};
	void Draw(const Model& model, Primitive type);
	void DrawLine(Eigen::Vector3i begin, Eigen::Vector3i end, Eigen::Vector3i color = Eigen::Vector3i{255, 255, 255});
	int GetIndex(int x,int y);

	const std::vector<Eigen::Vector3i>& FrameBuffer() const { return frame_buffer; }
	void SetFrameBuffer(std::vector<Eigen::Vector3i> vec) { frame_buffer = vec; }
private:
	std::uint16_t width;
	std::uint16_t height;

	std::vector<Eigen::Vector3i> frame_buffer;
};
