#include"Rasterizer.h"

Rasterizer::Rasterizer(int w, int h):width(w),height(h){
	frame_buffer.resize(w * h);
	depth_buffer.resize(w * h);
}

void Rasterizer::SetModelTransformation(){ model_transform = Eigen::Matrix4f::Identity(); }

void Rasterizer::SetViewTransformation(Eigen::Vector3f eye_pos, Eigen::Vector3f eye_direction)
{
	//创建单位矩阵，使用了Matrix4f中的静态函数
	Eigen::Matrix4f view = Eigen::Matrix4f::Identity();
	//TODO:旋转
	if(eye_direction.normalized() != Eigen::Vector3f{0, 0, -1})
	{
		float cos_angle = (eye_direction.dot(Eigen::Vector3f{0, 0, -1})) / eye_direction.norm();
		Eigen::Vector3f rotation_reel = (eye_direction.cross(Eigen::Vector3f{0, 0, -1})).normalized();
		//Rodrigued公式构建旋转矩阵
		Eigen::Matrix3f temporary = Eigen::Matrix3f::Identity();
		temporary *= cos_angle * temporary + (1 - cos_angle) * rotation_reel * rotation_reel.transpose() + std::sqrt(1 - cos_angle * cos_angle) * Eigen::Matrix3f{
			{0, -rotation_reel.z(), rotation_reel.y()},
			{rotation_reel.z(), 0, -rotation_reel.x()},
			{-rotation_reel.y(), rotation_reel.x(), 0}
		};
		view *= Eigen::Matrix4f{
			{temporary(0, 0), temporary(0, 1), temporary(0, 2), 0},
			{temporary(1, 0), temporary(1, 1), temporary(1, 2), 0},
			{temporary(2, 0), temporary(2, 1), temporary(2, 2), 0},
			{0, 0, 0, 1}
		};
	}
	//TODO:平移
	view *= Eigen::Matrix4f{
		{0, 0, 0, -eye_pos.x()},
		{0, 0, 0, -eye_pos.y()},
		{0, 0, 0, -eye_pos.z()},
		{0, 0, 0, 1}
	};
	view_transform = view;
}

void Rasterizer::SetPerspectiveTransformation(float fov, float aspect_ratio, float z_near, float z_far, bool is_perspective){
	Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
	if(is_perspective){
		//TODO：构建透视矩阵
		projection *= Eigen::Matrix4f{
			{z_near, 0, 0, 0},
			{0, z_near, 0, 0},
			{0, 0, z_near + z_far, -z_near * z_far},
			{0, 0, 1, 0}
		};
	}
	//TODO:构建正交矩阵
	float height = std::tan(fov / 2) * z_near * 2;
	float width = height * aspect_ratio;
	float depth = z_far - z_near;
	projection *= Eigen::Matrix4f{
		{2 / width, 0, 0, 0},
		{0, 2 / height, 0, 0, 0},
		{0, 0, 2 / depth, 0},
		{0, 0, 0, 1}
	};
	projection *= Eigen::Matrix4f{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, -(z_near + z_far) / 2},
		{0, 0, 0, 1},
	};
	perspective_transform = projection;
}

void Rasterizer::SetViewportTransformation(float viewport_width, float viewport_height){
	Eigen::Matrix4f viewport = Eigen::Matrix4f::Identity();
	viewport *= Eigen::Matrix4f{
		{viewport_width / 2, 0, 0, viewport_width / 2},
		{0, viewport_height / 2, 0, viewport_height / 2},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
	viewport_transform = viewport;
}

void Rasterizer::SetDepthBuffer(const Triangle& triangle){
	
}