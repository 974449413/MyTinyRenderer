#include "Texture.h"

void Texture::UncompressRLE(std::ifstream& in, std::uint8_t* data, const unsigned long& length){
    unsigned long current_pixel_pos = 0;
	std::uint8_t rgb[3];
    std::uint8_t flag;
    do{
		flag = in.get();
        if (!in.good()) {
            std::cerr<<current_pixel_pos<<std::endl;
			std::cerr << "an error occured while reading the data\n";
			return;
		}

        if(flag < 128){
            //首位为0，不重复存放flag+1个rgb颜色
			++flag;
			for (int i = 0; i < flag; i++) {
				in.read((char*)rgb, 3);
				data[current_pixel_pos++] = rgb[0];
				data[current_pixel_pos++] = rgb[1];
				data[current_pixel_pos++] = rgb[2];
			}
        }
        else{
            //首位为1，重复
            flag -= 127;
			in.read((char*)rgb, 3);
			for (int i = 0; i < flag; i++) {
				data[current_pixel_pos++] = rgb[0];
				data[current_pixel_pos++] = rgb[1];
				data[current_pixel_pos++] = rgb[2];
			}
        }
    } while (current_pixel_pos < length);
}

Texture::Texture(const char* file_name){
	std::ifstream in;
	in.open(file_name, std::ios::binary);
	if (!in.is_open()) {
		std::cerr << "can't open file:" << *file_name << std::endl;
		return;
	}
	TGA_Header header;
	in.read((char*)&header, sizeof(header));
	if(!in.good()){
		in.close();
		std::cerr<<"error in read TGA header"<<std::endl;
		return;
	}
    width = header.width;
    height = header.height;
	unsigned long length = static_cast<size_t>(header.width) * header.height * header.bitsPerPixel / 8;
	std::uint8_t* data = new std::uint8_t[length];
	memset((void*)data, 0, length);
    if (3 == header.imageType || 2 == header.imageType) {
		in.read((char*)data, length);
		if (!in.good()) {
			in.close();
			std::cerr << "an error occured while reading the data\n";
			return;
		}
	}
	else if (10 == header.imageType || 11 == header.imageType) {
        UncompressRLE(in, data, length);
		if (!in.good()) {
			in.close();
			std::cerr << "an error occured while reading the data2\n";
			return;
		}
	}
	if (((header.imageDescriptor << 3) & 0b0) == 0) {
		for (int i = header.height - 1; i >= 0; --i) {
			int count = i * header.width * 3;
			for (int j = 0; j < header.width; ++j) {
				Eigen::Vector3i temporary;
				temporary.z() = data[count++];
				temporary.y() = data[count++];
				temporary.x() = data[count++];
				color.push_back(temporary);
			}
		}
	}
	else {
		int count = 0;
		for (int i = 0; i < header.height * header.width; ++i) {
			Eigen::Vector3i temporary;
			temporary.z() = data[count++];
			temporary.y() = data[count++];
			temporary.x() = data[count++];
			color.push_back(temporary);
		}
	}
	in.close();
}

Eigen::Vector3i Texture::GetColor(float x, float y) const {
    int new_x = (x - std::floor(x)) * (width - 1);
    /*int new_y = height - 1 - (y - std::floor(y)) * (height - 1);*/
	int new_y = (y - std::floor(y)) * (height - 1);
	int index = 0;
	index += new_y * width;
	index += new_x;
    return color.at(index);
}