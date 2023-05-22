#pragma once
#include <fstream>
#include <iostream>
#include "Rasterizer.h"

#pragma pack(push,1)
typedef struct _TGAHEAD {
	std::uint8_t length;		//0x00 ��ɫ�����ܳ��ȣ����ֽ�Ϊ��λ
	std::uint8_t colorMapType;	//0x01 �Ƿ�ʹ����ɫ��
	std::uint8_t imageType;	//0x02 ͼ�������

	std::uint16_t colorMapStart;	//0x03 ��һ����ɫ������ 
	std::uint16_t colorMapLength;//0x05 ��ɫ������
	std::uint8_t colorMapDepth;	//0x07 ��ɫ��λ��

	std::uint16_t xOriginPos;	//0x08 ͼ��xԭ��
	std::uint16_t yOriginPos;	//0x0A ͼ��yԭ��
	std::uint16_t width;		//0x0C ͼ�����
	std::uint16_t height;	//0x0E ͼ��߶�
	std::uint8_t bitsPerPixel;	//0x10 ͼ����ÿ��������ռ��λ��
	std::uint8_t imageDescriptor;	//0x11 ͼ�������ֽ�
}TGA_Header;
#pragma pack(pop)

class Rasterizer;

class TGAImage {
public:
	TGAImage(std::uint16_t h, std::uint16_t w);
	~TGAImage() { delete[] data; }
	bool WriteTGAImage(const char* filename);
	static bool ReadTGAImage(const char* filename, std::vector<Eigen::Vector3f> texture_data);
	void SetTGAImage(const Rasterizer& rasterizer);
private:
	TGA_Header header;
	std::uint16_t width;
	std::uint16_t height;
	std::uint8_t* data;
};