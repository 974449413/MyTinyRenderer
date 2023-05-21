#pragma once
#include <fstream>
#include <iostream>
#include "Rasterizer.h"

#pragma pack(push,1)
typedef struct _TGAHEAD {
	std::uint8_t length;		//0x00 颜色表的总长度，以字节为单位
	std::uint8_t colorMapType;	//0x01 是否使用颜色表
	std::uint8_t imageType;	//0x02 图像的类型

	std::uint16_t colorMapStart;	//0x03 第一个颜色表索引 
	std::uint16_t colorMapLength;//0x05 颜色表长度
	std::uint8_t colorMapDepth;	//0x07 颜色表位数

	std::uint16_t xOriginPos;	//0x08 图像x原点
	std::uint16_t yOriginPos;	//0x0A 图像y原点
	std::uint16_t width;		//0x0C 图像宽度
	std::uint16_t height;	//0x0E 图像高度
	std::uint8_t bitsPerPixel;	//0x10 图像中每个像素所占的位数
	std::uint8_t imageDescriptor;	//0x11 图像描述字节
}TGA_Header;
#pragma pack(pop)

class TGAImage {
public:
	TGAImage(std::uint16_t h, std::uint16_t w);
	~TGAImage() { delete[] data; }
	bool WriteTGAImage(const char* filename);
	void SetTGAImage(const Rasterizer& rasterizer);
private:
	TGA_Header header;
	std::uint16_t width;
	std::uint16_t height;
	std::uint8_t* data;
};