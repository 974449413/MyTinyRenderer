//调整默认的内存对齐方式，节省内存
#pragma once
#include<cstdint>

#pragma pack(push,1)
typedef struct _TGAHEAD{
	std::uint8_t length;		//0x00 HEADER的总长度，以字节为单位
	std::uint8_t colorMapType;	//0x01 是否使用颜色表
	std::uint8_t imageType;	//0x02 图像的类型
	
	std::uint16_t colorMapStart;	//0x03 第一个颜色表索引 
	std::uint16_t colorMapLength;//0x05 颜色表长度
	std::uint8_t colorMapDepth;	//0x07 颜色表位数

	std::uint16_t xOriginPos;	//0x08 图像x原点
	std::uint16_t yOriginPos;	//0x0A 图像y原点
	std::uint16_t width;		//0x0C 图像宽度
	std::uint16_t height;	//0x0E 图像高度
	std::uint16_t pixelDepth;	//0x10 图像中每个像素所占的位数
}TGA_Header;
#pragma pack(pop)

class TGA_Image{
public:
	TGA_Image() {}	//默认构造函数
	TGA_Image(const int& width, const int& height);	//构造函数
private:
	std::uint16_t width;
	std::uint16_t height;
};
