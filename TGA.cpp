#include"TGA.h"

TGA_Image::TGA_Image(const std::uint16_t& width, const std::uint16_t& height, PixelColorType type):width(width),height(height),pixel_color_type(type),data(nullptr){}

bool TGA_Image::Write(const std::string filename){
	std::ofstream out;
	out.open(filename, std::ofstream::binary);
	if(!out.is_open()){
		std::cerr<<"无法打开文件: "<<filename<<std::endl;
		return false;
	}
	TGA_Header header;
	memset(&header, 0, sizeof(header));
	header.imageType = (std::uint16_t)pixel_color_type;
	header.width = width;
	header.height = height;
}
