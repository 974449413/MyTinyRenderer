#include "TGA.h"

TGAImage::TGAImage(std::uint16_t h, std::uint16_t w) : width(w),height(h){
	memset((void*)&header, 0, sizeof(header));
	//低尾端
	header.imageType = 2;
	header.width = width;
	header.height = height;
	header.bitsPerPixel = 24;
	header.imageDescriptor = 0b00100000; // 第四位：0表示从左到右，1表示从右到左;第五位：1表示从上到下，0表示从下到上

	data = new std::uint8_t[static_cast<size_t>(width) * height * header.bitsPerPixel / 3];
}

bool TGAImage::WriteTGAImage(char* filename) {
	std::ofstream out;
	out.open(filename, std::ofstream::binary);
	if (!out.is_open()) {
		std::cerr << "打开文件失败:" << *filename << std::endl;
		return false;
	}
	out.write((char*)&header, sizeof(header));
	out.write((char*)data, static_cast<size_t>(3) * width * height);
	return true;
}

void TGAImage::SetTGAImage(const Rasterizer& rasterizer) {
	int count = 0;
	for (int i = 0; i < height * width; ++i) {
		data[count++] = static_cast<int>(rasterizer.FrameBuffer()[i].z());
		data[count++] = rasterizer.FrameBuffer()[i].y();
		data[count++] = rasterizer.FrameBuffer()[i].x();
	}
}