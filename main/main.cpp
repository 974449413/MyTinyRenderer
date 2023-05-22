#include <fstream>
#include <iostream>
#include <eigen3/Eigen/Eigen>
#include "TGA.h"
#include "Model.h"

constexpr std::uint16_t height = 800;
constexpr std::uint16_t width = 800;

const std::string file1 = "F:/github/MyTinyRenderer/main/african_head.obj";
const std::string file2 = "african_head.obj";
const std::string output = "main.tga";

int main(int argc, char** argv)
{
	std::string file = file1;
	if (argc > 1) {
		file = argv[1];
	}
	Model model(file.c_str());
	TGAImage image(height, width);
	Rasterizer rasterizer_object(height, width);
	rasterizer_object.Draw(model, Rasterizer::Primitive::Line);
	image.SetTGAImage(rasterizer_object);
	if (!image.WriteTGAImage(output.c_str())) {
		std::cerr << "输入文件:" << argv[1] << "失败" << std::endl;
		return -1;
	}
	return 0;
}
