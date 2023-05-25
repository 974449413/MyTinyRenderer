#include "TGA.h"

TGAImage::TGAImage(std::uint16_t h, std::uint16_t w) : width(w),height(h){
	memset((void*)&header, 0, sizeof(header));
	//��β��
	header.imageType = 2;
	header.width = width;
	header.height = height;
	header.bitsPerPixel = 24;
	header.imageDescriptor = 0b00100000; // ����λ��0��ʾ�����ң�1��ʾ���ҵ���;����λ��1��ʾ���ϵ��£�0��ʾ���µ���

	data = new std::uint8_t[static_cast<size_t>(width) * height * header.bitsPerPixel / 8];
	z_buffer_data = new std::uint8_t[static_cast<size_t>(width) * height * header.bitsPerPixel / 8];
	//memset(data, 0, static_cast<size_t>(width) * height * header.bitsPerPixel / 3);
}

bool TGAImage::WriteTGAImage(const char* filename, bool is_z_buffer) {
	std::ofstream out;
	out.open(filename, std::ofstream::binary);
	if (!out.is_open()) {
		std::cerr << "���ļ�ʧ��:" << *filename << std::endl;
		return false;
	}
	out.write((char*)&header, sizeof(header));
	if (is_z_buffer) {
		out.write((char*)z_buffer_data, static_cast<size_t>(3) * width * height);
	}
	else {
		out.write((char*)data, static_cast<size_t>(3) * width * height);
	}
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

void TGAImage::SetZBufferTGAImage(std::vector<float> z_buffer) {
	int length = height * width;
	int index = 0;
	int count = 0;
	while (index < length) {
		if (index == 359664) {
			int t = 20;
		}
		float z = z_buffer.at(index);
		float rate = (z + 1) / 2;
		if (rate >= 0) {
			int t;
		}
		if (rate <= 0) {
			z_buffer_data[count++] = 0;
			z_buffer_data[count++] = 0;
			z_buffer_data[count++] = 0;
		}
		else if (rate >= 1) {
			z_buffer_data[count++] = 255;
			z_buffer_data[count++] = 255;
			z_buffer_data[count++] = 255;
		}
		else {
			z_buffer_data[count++] = 255 * rate;
			z_buffer_data[count++] = 255 * rate;
			z_buffer_data[count++] = 255 * rate;
		}
		++index;
	}
}