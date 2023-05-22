#include "TGA.h"

TGAImage::TGAImage(std::uint16_t h, std::uint16_t w) : width(w),height(h){
	memset((void*)&header, 0, sizeof(header));
	//��β��
	header.imageType = 2;
	header.width = width;
	header.height = height;
	header.bitsPerPixel = 24;
	header.imageDescriptor = 0b00100000; // ����λ��0��ʾ�����ң�1��ʾ���ҵ���;����λ��1��ʾ���ϵ��£�0��ʾ���µ���

	data = new std::uint8_t[static_cast<size_t>(width) * height * header.bitsPerPixel / 3];
	//memset(data, 0, static_cast<size_t>(width) * height * header.bitsPerPixel / 3);
}

bool TGAImage::WriteTGAImage(const char* filename) {
	std::ofstream out;
	out.open(filename, std::ofstream::binary);
	if (!out.is_open()) {
		std::cerr << "���ļ�ʧ��:" << *filename << std::endl;
		return false;
	}
	out.write((char*)&header, sizeof(header));
	out.write((char*)data, static_cast<size_t>(3) * width * height);
	out.close();
	return true;
}

void TGAImage::SetTGAImage(const Rasterizer& rasterizer) {
	int count = 0;
	for (int i = 0; i < height * width; ++i) {
		data[count++] = rasterizer.FrameBuffer()[i].z();
		data[count++] = rasterizer.FrameBuffer()[i].y();
		data[count++] = rasterizer.FrameBuffer()[i].x();
	}
}

bool TGAImage::ReadTGAImage(const char* filename, std::vector<Eigen::Vector3f> texture_data){
	std::ifstream in;
	in.open(filename, std::ifstream::binary);
	if (!in.is_open()) {
		std::cerr << "���ļ�ʧ��:" << *filename << std::endl;
		return false;
	}
	TGA_Header header;
	in.read((char*)&header, sizeof(header));
	if(!in.good()){
		in.close();
		std::cerr<<"error in read TGA header"<<std::endl;
		return false;
	}
	unsigned long length = static_cast<size_t>(header.width) * header.height * header.bitsPerPixel / 3;
	std::uint8_t* data = new std::uint8_t[length];
	in.read((char*)data, length);
	if(!in.good()){
		in.close();
		std::cerr<<"error in read TGA header"<<std::endl;
		return false;
	}
	int count = 0;
	for (int i = 0; i < header.height * header.width; ++i) {
		Eigen::Vector3f temporary;
		temporary.z() = data[count++];
		temporary.y() = data[count++];
		temporary.x() = data[count++];
		texture_data.push_back(temporary);
	}
	in.close();
	return true;
}