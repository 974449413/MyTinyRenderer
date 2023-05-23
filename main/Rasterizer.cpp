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

void Rasterizer::Draw(const Model& model, Primitive type){
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
		
	}
}

