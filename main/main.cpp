#include <fstream>

#pragma pack(push,1)
typedef struct _TGAHEAD{
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

int main(int argc, char** argv)
{
	std::ofstream out;
	out.open(argv[1], std::ios::binary);

	TGA_Header header;
	memset((void*)&header, 0, sizeof(header));
	header.imageType = 2;
	header.width = 700;
	header.height = 700;
	header.bitsPerPixel = 24;
	header.imageDescriptor = 0b00100000; // top-left origin

	out.write((char*)&header, sizeof(header));

	char data[700 * 700 * 3];
	memset((void*)data, 0, sizeof(data));
	out.write((char*)data, sizeof(data));
	return 0;
}