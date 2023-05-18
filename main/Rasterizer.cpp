#include "Rasterizer.h"

void Rasterizer::DrawLine(Eigen::Vector3i begin, Eigen::Vector3i end, Eigen::Vector3i color){
	int x0 = begin.x();
	int y0 = begin.y();
	int x1 = end.x();
	int y1 = end.y();
	if (x0 < 0 || x0 >= width || x1 < 0 || x1 >= width || y0 < 0 || y0 >= height || y0 < 0 || y0 >= height) {
		std::cerr << "error in range" << std::endl;
	}
	if (x0 == x1 && y0 == y1)
	{
		frame_buffer.at(GetIndex(x0, y0)) = color ;
		return;
	}
	bool is_symmetry = false;

	if((y1 - y0) > (x1 - x0)){
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
			frame_buffer.at(GetIndex(y, x)) = color;
		}
		else {
			frame_buffer.at(GetIndex(x, y)) = color;
		}
		distance += dy;
		if(distance >= 0.5){
			y += 1;
			distance -= 1;
		}
	}
}

int Rasterizer::GetIndex(int x,int y){
	int new_y = 699 - y;
	int new_x = x;
	int index = 0;
	index += new_y * width;
	index += new_x;
	return index;
}
