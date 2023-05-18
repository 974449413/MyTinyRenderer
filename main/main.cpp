#include <fstream>
#include <iostream>
#include <eigen3/Eigen/Eigen>
#include "TGA.h"

constexpr std::uint16_t height = 700;
constexpr std::uint16_t width = 700;

std::vector<Eigen::Vector3f> vertex;
std::vector<Eigen::Vector3i> face;

//读取obj
void read() {
	std::ifstream in;
	//in.open("F:/github/MyTinyRenderer/main/african_head.obj", std::ifstream::in);
	in.open("african_head.obj", std::ifstream::in);
	if (!in.is_open()) {
		std::cerr << in.rdstate() << std::endl;
		std::cerr << "failed open obj file " << std::endl;
	}

	std::string line;
	while (!in.eof()) {
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		if (line.compare(0, 2, "v ") == 0) {
			iss >> trash;
			Eigen::Vector3f v;
			for (int i = 0; i < 3; i++) {
				iss >> v[i];
			}
			vertex.push_back(v);
		}
		else if (line.compare(0, 2, "f ") == 0) {
			iss >> trash;
			Eigen::Vector3i f;
			for (int i = 0; i < 3; i++) {
				iss >> f[i];
				iss >> trash;
			}
			face.push_back(f);
		}
	}
}

int main(int argc, char** argv)
{
	if (argv[1] == nullptr)
	{
		std::cerr << "please input file" << std::endl;
		return -1;
	}
	read();
	TGAImage image(height, width);
	Rasterizer rasterizer_object(height, width);

	rasterizer_object.DrawLine(Eigen::Vector3i{0,0,3}, Eigen::Vector3i{ 699,699,0 });
	rasterizer_object.DrawLine(Eigen::Vector3i{500,0,3 }, Eigen::Vector3i{ 500,699,0 });
	/*for (int i = 0; i < face.size(); i++) {
		Eigen::Vector3f point = face[i];
		for (int j = 0; j < 3; j++) {
			Eigen::Vector3f point = vertex.at(face.at(i)[j]);
			Eigen::Vector3i begin = {
				static_cast<int>(point.x() * width / 2),
				static_cast<int>(point.y() * height / 2),
				0
			};
			point = vertex.at(face.at(i)[(j + 1) % 3]);
			Eigen::Vector3i end = {
				static_cast<int>(point.x() * width / 2),
				static_cast<int>(point.y() * height / 2),
				0
			};
			if (begin.y() <= height - 1 && end.y() <= height - 1 && begin.x() >= 0 && end.x() >= 0 && begin.y() >= 0 && end.y() >= 0 && begin.x() <= width - 1 && end.x() <= width - 1) {
				rasterizer_object.DrawLine(begin, end);
			}
		}
	}*/
	/*for (auto f : face) {
		for (int i = 0; i < 3; i++)
		{
			Eigen::Vector3f point = vertex.at(f[i]);
			Eigen::Vector3i begin = {
				static_cast<int>(point.x() * width / 2),
				static_cast<int>(point.y() * height / 2),
				0
			};
			point = vertex.at(f[(i + 1) % 3]);
			Eigen::Vector3i end = {
				static_cast<int>(point.x() * width / 2),
				static_cast<int>(point.y() * height / 2),
				0
			};
			if (begin.y() <= height - 1 && end.y() <= height - 1 && begin.x() >= 0 && end.x() >= 0 && begin.y() >= 0 && end.y() >= 0 && begin.x() <= width - 1 && end.x() <= width - 1) {
				rasterizer_object.DrawLine(begin, end);
			}
		}
	}*/
	// for (int i = 0; i  <face.size(); i++) {
	// 	Eigen::Vector3i face2 = face.at(i);
	// 	for (int j = 0; j < 3; j++) {
	// 		if (face2[j] >= 0 && face2[j] < vertex.size() && face2[(j + 1) % 3] >= 0 && face2[(j + 1) % 3] < vertex.size()) {
	// 			Eigen::Vector3f v0 = vertex.at(face2[j]);
	// 			Eigen::Vector3f v1 = vertex.at(face2[(j + 1) % 3]);
	// 			int x0 = (v0.x() + 1.) * width / 2.;
	// 			int y0 = (v0.y() + 1.) * height / 2.;
	// 			int x1 = (v1.x() + 1.) * width / 2.;
	// 			int y1 = (v1.y() + 1.) * height / 2.;

	// 			if (y0 <= height - 1 && y1 <= height - 1 && x0 >= 0 && x1 >= 0 && y0 >= 0 && y1 >= 0 && x0 <= width - 1 && x1 <= width - 1) {
	// 				rasterizer_object.DrawLine(Eigen::Vector3i{ x0, y0, 0 }, Eigen::Vector3i{ x1, y1, 0 });
	// 			}
	// 		}
	// 	}
	// }

	image.SetTGAImage(rasterizer_object);
	if (!image.WriteTGAImage(argv[1])) {
		std::cerr << "输入文件:" << argv[1] << "失败" << std::endl;
		return -1;
	}
	return 0;
}
