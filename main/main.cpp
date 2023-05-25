#include <fstream>
#include <iostream>
#include <eigen3/Eigen/Eigen>
#include "TGA.h"
#include "Model.h"
#include "Rasterizer.h"
#include "Texture.h"

constexpr std::uint16_t height = 800;
constexpr std::uint16_t width = 800;

const std::string file1 = "F:/github/MyTinyRenderer/main/african_head/african_head.obj";
const std::string file2 = "african_head/african_head.obj";

const std::string file3 = "F:/github/MyTinyRenderer/main/african_head/african_head_diffuse.tga";
const std::string file4 = "african_head/african_head_diffuse.tga";

const std::string output = "frame_buffer.tga";

const Eigen::Vector3f light_dir{ 0,0,-1 }; // light source

int main(int argc, char** argv)
{
	// std::string file = file2;
	// if (argc > 1) {
	// 	file = argv[1];
	// }
	Model model(file1.c_str());
	TGAImage image(height, width);
	Rasterizer rasterizer_object(height, width);
	Texture texture(file3.c_str());

	//write to frame_buffer.tga
	rasterizer_object.Draw(model, texture);
	image.SetTGAImage(rasterizer_object);
	if (!image.WriteTGAImage(output.c_str())) {
		std::cerr << "输入文件:" << argv[1] << "失败" << std::endl;
		return -1;
	}

	//write to z_buffer.tga
	image.SetZBufferTGAImage(rasterizer_object.ZBuffer());
	if (!image.WriteTGAImage("zbuffer.tga", true)) {
		std::cerr << "输入文件:" << argv[1] << "失败" << std::endl;
		return -1;
	}

	return 0;
}
