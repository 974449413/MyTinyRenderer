#include "Rasterizer.h"
#include "Model.h"

void Rasterizer::DrawLine(Eigen::Vector3i begin, Eigen::Vector3i end, Eigen::Vector3i color){
	int x0 = begin.x();
	int y0 = begin.y();
	int x1 = end.x();
	int y1 = end.y();
	if (x0 == x1 && y0 == y1)
	{
		frame_buffer.at(GetIndex(x0, y0)) = color ;
		return;
	}
	bool is_symmetry = false;

	if(std::abs(y1 - y0) > std::abs(x1 - x0)){
		std::swap(x0, y0);
		std::swap(x1, y1);
		is_symmetry = true;
	}
	
	if(x0 > x1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	
	float dy = (float)(y1 - y0) / (float)(x1 - x0);
	float distance = 0.;
	int y = y0;
	for(int x = x0;x<= x1;++x){
		if (is_symmetry) {
			if (x0 < 0 || x0 >= width || x1 < 0 || x1 >= width || y0 < 0 || y0 >= height || y1 < 0 || y1 >= height) {
				std::cerr << "error in range" << std::endl;
			}
			else {
				frame_buffer.at(GetIndex(y, x)) = color;
			}
		}
		else {
			if (x0 < 0 || x0 >= width || x1 < 0 || x1 >= width || y0 < 0 || y0 >= height || y1 < 0 || y1 >= height) {
				std::cerr << "error in range" << std::endl;
			}
			else {
				frame_buffer.at(GetIndex(x, y)) = color;
			}
		}
		distance += dy;
		if(std::abs(distance) >= 0.5){
			y += dy > 0 ? 1 : -1;
			distance -= dy > 0 ? 1. : -1.;
		}
	}
}

int Rasterizer::GetIndex(int x,int y){
	int new_y = height - y - 1;
	int new_x = x;
	int index = 0;
	index += new_y * width;
	index += new_x;
	return index;
}

void Rasterizer::Draw(const Model& model, const Texture& texture, Primitive type){
	if(type == Primitive::Line){
		for (int i = 0; i  <model.face.size(); i++) {
			Eigen::Vector3i face2 = model.face.at(i);
			for (int j = 0; j < 3; j++) {
				Eigen::Vector3i begin,end;
				Eigen::Vector3f v0 = model.vertex.at(face2[j]);
				Eigen::Vector3f v1 = model.vertex.at(face2[(j + 1) % 3]);
				begin.x() = (v0.x() + 1.) * width / 2.;
				begin.y() = (v0.y() + 1.) * height / 2.;
				end.x() = (v1.x() + 1.) * width / 2.;
				end.y() = (v1.y() + 1.) * height / 2.;
				DrawLine(begin, end);
			}
		}
	}
	else if(type == Primitive::Triangle){
		int index = 0;
		while(index < model.face.size()){
			std::cerr << index  << " ";
			Eigen::Vector3i point[3];
			Eigen::Vector3i color[3];
			Eigen::Vector3f normal[3];
			for (int i = 0; i < 3; i++) {
				Eigen::Vector3f temporary = model.vertex.at(model.face.at(index)[i]);
				point[i].x() = static_cast<int>((temporary.x() + 1.) * width / 2.);
				point[i].y() = static_cast<int>((temporary.y() + 1.) * width / 2.);
				point[i].z() = static_cast<int>(temporary.z());

				Eigen::Vector3f uv = model.texture.at(model.face_texture.at(index)[i]);
				color[i] = texture.GetColor(uv.x(), uv.y());

				normal[i] = model.normal.at(model.face_normal.at(index)[i]);
			}
			DrawTriangle(point, color, normal);
			++index;
		}
	}
}

float CalculateArea(Eigen::Vector3f* point) {
	Eigen::Vector3f a = { static_cast<float>((point + 1)->x() - point->x()), static_cast<float>((point + 1)->y() - point->y()), 0 };
	Eigen::Vector3f b = { static_cast<float>((point + 2)->x() - point->x()),static_cast<float>((point + 2)->y() - point->y()), 0 };
	Eigen::Vector3f r = a.cross(b);
	return r.norm() / 2;
}

bool IsInTriangle(Eigen::Vector3i* point, float x, float y, float& u, float& v, float& t) {
	Eigen::Vector3f v1 = { static_cast<float>((point + 1)->x() - point->x()), static_cast<float>((point + 1)->y() - point->y()), 0 };
	Eigen::Vector3f v2 = { static_cast<float>((point + 2)->x() - (point + 1)->x()), static_cast<float>((point + 2)->y() - (point + 1)->y()), 0 };
	Eigen::Vector3f v3 = { static_cast<float>(point->x() - (point + 2)->x()), static_cast<float>(point->y() - (point + 2)->y()), 0 };

	Eigen::Vector3f target_v1 = { x - point->x(), y - point->y(), 0 };
	Eigen::Vector3f target_v2 = { x - (point + 1)->x(), y - (point + 1)->y(), 0 };
	Eigen::Vector3f target_v3 = { x - (point + 2)->x(), y - (point + 2)->y(), 0 };

	float z1 = v1.cross(target_v1).z();
	float z2 = v2.cross(target_v2).z();
	float z3 = v3.cross(target_v3).z();

	Eigen::Vector3f a_point[3] = {
		point->cast<float>(),
		(point + 1)->cast<float>(),
		(point + 2)->cast<float>(),
	};
	float area = CalculateArea(a_point);

	Eigen::Vector3f u_point[3] = {
		{x, y, 0},
		(point + 1)->cast<float>(),
		(point + 2)->cast<float>(),
	};
	u = CalculateArea(u_point) / area;

	Eigen::Vector3f v_point[3] = {
		{x, y, 0},
		point->cast<float>(),
		(point + 2)->cast<float>(),
	};
	v = CalculateArea(v_point) / area;

	Eigen::Vector3f t_point[3] = {
		{x, y, 0},
		point->cast<float>(),
		(point + 1)->cast<float>(),
	};
	t = CalculateArea(t_point) / area;

	if ((z1 > 0 && z2 > 0 && z3 > 0) || (z1 < 0 && z2 < 0 && z3 < 0)) {
		return true;
	}

	return false;
}

void Rasterizer::DrawTriangle(Eigen::Vector3i* point, Eigen::Vector3i* color, Eigen::Vector3f* normal){
	//包围盒
	int left = std::min(point->x(), std::min((point+1)->x(), (point+2)->x()));	
	int right = std::max(point->x(), std::max((point+1)->x(), (point+2)->x()));	
	int down = std::min(point->y(), std::min((point+1)->y(), (point+2)->y()));
	int up = std::max(point->y(), std::max((point+1)->y(), (point+2)->y()));

	//逐像素判断
	for (int x = left; x <= right; ++x) {
		for (int y = down; y <= up; ++y) {
			float u, v, t;
			if (IsInTriangle(point, x + 0.5, y + 0.5, u, v, t)) {
				Eigen::Vector3f new_normal = {
					normal->x() * u + (normal + 1)->x() * v + (normal + 2)->x() * t,
					normal->y() * u + (normal + 1)->y() * v + (normal + 2)->y() * t,
					normal->z() * u + (normal + 1)->z() * v + (normal + 2)->z() * t,
				};
				Eigen::Vector3f direct = { 0, 0, 1 };
				new_normal = new_normal.normalized();
				if (direct.dot(new_normal) > 0) {
					float intensity = direct.dot(new_normal);
					Eigen::Vector3i new_color = {
					static_cast<int>((color->x() * u + (color + 1)->x() * v + (color + 2)->x() * t) * intensity),
					static_cast<int>((color->y() * u + (color + 1)->y() * v + (color + 2)->y() * t) * intensity),
					static_cast<int>((color->z() * u + (color + 1)->z() * v + (color + 2)->z() * t) * intensity),
					};
					frame_buffer[GetIndex(x, y)] = new_color;
				}
			}
		}
	}
}
