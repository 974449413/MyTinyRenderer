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
		model_transform = Eigen::Matrix4f::Identity();
		view_transform = Eigen::Matrix4f::Identity();
		perspective_transform = Eigen::Matrix4f::Identity();
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
	
	void SetModelTransformation();
	void SetViewTransformation(Eigen::Vector3f eye_pos, Eigen::Vector3f eye_direction = Eigen::Vector3f{ 0, 0, 0 });
	void SetPerspectiveTransformation(float fov, float aspect_ratio, float z_near, float z_far, bool is_perspective = true);

	Eigen::Vector4f TransformToHomogeneout(Eigen::Vector3f point);
	Eigen::Vector3f TransformToNormal(Eigen::Vector4f point);
	
private:
	void SetFrameBuffer(std::vector<Eigen::Vector3i> vec) { frame_buffer = vec; }
	void DrawTriangle(Eigen::Vector3f* point, Eigen::Vector3f* uv, Eigen::Vector3f* normal, const Texture& texture);
	void DrawLine(Eigen::Vector3i begin, Eigen::Vector3i end, Eigen::Vector3i color = Eigen::Vector3i{ 255, 255, 255 });
private:
	std::uint16_t width;
	std::uint16_t height;

	std::vector<Eigen::Vector3i> frame_buffer;
	std::vector<float> z_buffer;

	Eigen::Matrix4f model_transform;
	Eigen::Matrix4f view_transform;
	Eigen::Matrix4f perspective_transform;
};
