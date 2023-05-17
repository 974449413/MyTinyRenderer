#include"Rasterizer.h"

Rasterizer::Rasterizer(int h, int w):width(w),height(h){
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
		{0, 2 / height, 0, 0},
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

void Rasterizer::SetViewportTransformation(float viewport_height, float viewport_width){
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

int Rasterizer::GetBufferIndex(int x, int y){
	return y * width + x;
}

void Rasterizer::DrawLine(Eigen::Vector2i begin, Eigen::Vector2i end){
	bool is_change_slope = false;
	//1.转斜率
	if(std::abs(end.y() - begin.y()) > std::abs(end.x() - begin.x()))
	{
		is_change_slope = true;
		std::swap(begin.x(), begin.y());
		std::swap(end.x(), end.y());
	}
	//2.转起点
	if(begin.x() > end.x())
	{
		std::swap(begin, end);
	}
	//3.画线
	int dx = end.x() - begin.x();
	int dy = end.y() - begin.y();
	float derror = std::abs(dy / float(dx));
	float error = 0;
	int y = begin.y();
	for(int x = begin.x(); x<=end.x(); ++x){
		if (is_change_slope) {
			frame_buffer[GetBufferIndex(y, x)] = Eigen::Vector3f{ 255, 0, 0 };
		}
		else {
			frame_buffer[GetBufferIndex(x, y)] = Eigen::Vector3f{ 255, 0, 0 };
		}
		error += derror;
		if (error > .5) {
			y += (end.y() > begin.y() ? 1 : -1);
			error -= 1.;
		}
		/*float t = (x - begin.x()) / (end.x() - begin.x());
		float y = begin.y() + (end.y() - begin.y()) * t;
		degree += y - std::abs(y);
		if(degree >= 0.5)
		{
			y = std::abs(y) + 1;
			degree -= 1;
		}
		else
		{
			y = std::abs(y);
		}
		if(is_change_slope)
		{
			frame_buffer[GetBufferIndex(y,x)] = Eigen::Vector3f{255, 0, 0};
		}
		else
		{
			frame_buffer[GetBufferIndex(x,y)] = Eigen::Vector3f{255, 0, 0};
		}*/
	}
}




void Rasterizer::draw_line2(Eigen::Vector3f begin, Eigen::Vector3f end)
{
	auto x1 = begin.x();
	auto y1 = begin.y();
	auto x2 = end.x();
	auto y2 = end.y();

	Eigen::Vector3f line_color = { 255, 255, 255 };

	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = fabs(dx);
	dy1 = fabs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;

	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		Eigen::Vector3f point = Eigen::Vector3f(x, y, 1.0f);
		frame_buffer[GetBufferIndex(x, y)] = Eigen::Vector3f{ 255, 0, 0 };
		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			//            delay(0);
			Eigen::Vector3f point = Eigen::Vector3f(x, y, 1.0f);
			frame_buffer[GetBufferIndex(x, y)] = Eigen::Vector3f{ 255, 0, 0 };
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}
		Eigen::Vector3f point = Eigen::Vector3f(x, y, 1.0f);
		frame_buffer[GetBufferIndex(x, y)] = Eigen::Vector3f{ 255, 0, 0 };
		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			//            delay(0);
			Eigen::Vector3f point = Eigen::Vector3f(x, y, 1.0f);
			frame_buffer[GetBufferIndex(x, y)] = Eigen::Vector3f{ 255, 0, 0 };
		}
	}
}
