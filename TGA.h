typedef struct _TGAHEAD{
	uint8_t length;		//0x00 HEADER的总长度，以字节为单位
	uint8_t colorMapType;	//0x01 是否使用颜色表
	uint8_t imageType;	//0x02 图像的类型
	
	uint16_t colorMapStart;	//0x03 第一个颜色表索引 
	uint16_t colorMapLength;//0x05 颜色表长度
	uint8_t colorMapDepth;	//0x07 颜色表位数

	uint16_t xOriginPos;	//0x08 图像x原点
	uint16_t yOriginPos;	//0x0A 图像y原点
	uint16_t width;		//0x0C 图像宽度
	uint16_t height;	//0x0E 图像高度
	uint16_t pixelDepth;	//0x10 图像中每个像素所占的位数
}TGA_Header;
