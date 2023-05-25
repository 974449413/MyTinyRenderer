#pragma once
#include <eigen3/Eigen/Eigen>
#include <algorithm>
#include <vector>
#include <iostream>
#include "Texture.h"

class Model;
class Texture;

class Rasterizer{
public:
	Rasterizer(std::uint16_t height, std::uint16_t width) : width(width),height(height) { 
		frame_buffer.resize(static_cast<size_t>(height) * width, Eigen::Vector3i{0, 0, 0});
		z_buffer.resize(static_cast<size_t>(height) * width, -std::numeric_limits<float>::max());
	}
public:
	enum class Primitive{
		Line,
		Triangle
	};
	void Draw(const Model& model, const Texture& texture, Primitive type = Primitive::Triangle);
	
	int GetIndex(int x,int y);

	const std::vector<Eigen::Vector3i>& FrameBuffer() const { return frame_buffer; }
	const std::vector<float>& ZBuffer() const { return z_buffer; }
	void SetFrameBuffer(std::vector<Eigen::Vector3i> vec) { frame_buffer = vec; }
	void DrawTriangle(Eigen::Vector3f* point, Eigen::Vector3f* uv, Eigen::Vector3f* normal, const Texture& texture);
	void DrawLine(Eigen::Vector3i begin, Eigen::Vector3i end, Eigen::Vector3i color = Eigen::Vector3i{ 255, 255, 255 });
private:
	
	
private:
	std::uint16_t width;
	std::uint16_t height;

	std::vector<Eigen::Vector3i> frame_buffer;
	std::vector<float> z_buffer;
};
