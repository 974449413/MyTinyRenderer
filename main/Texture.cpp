#include "Texture.h"

void Texture::UncompressRLE(std::ifstream& in, std::uint8_t* data, const unsigned long& length){
    unsigned long current_pixel_pos = 0;
    std::cerr<<length<<std::endl;
    std::uint8_t flag;
    do{
        in >> flag;
        if (!in.good()) {
            std::cerr<<current_pixel_pos<<std::endl;
			std::cerr << "an error occured while reading the data\n";
			return;
		}

        if(flag < 128){
            //首位为0，不重复
            ++flag;
            flag *= 3;
            in.read((char*)data, flag);
            current_pixel_pos += flag;
        }
        else{
            //首位为1，重复
            flag -= 127;
            flag *= 3;
            std::uint8_t temporary1;
            std::uint8_t temporary2;
            std::uint8_t temporary3;
            in >> temporary1;
            in >> temporary2;
            in >> temporary3;
            for(int i = 0;i < flag;i++){
                data[current_pixel_pos++] = temporary1;
                data[current_pixel_pos++] = temporary2;
                data[current_pixel_pos++] = temporary3;
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
	int count = 0;
	for (int i = 0; i < header.height * header.width; ++i) {
		Eigen::Vector3i temporary;
		temporary.z() = data[count++];
		temporary.y() = data[count++];
		temporary.x() = data[count++];
		color.push_back(temporary);
	}
	in.close();
}

Eigen::Vector3i Texture::GetColor(float x, float y){
    int new_x = std::floor(x) * (width - 1);
    int new_y = height - 1 - std::floor(y) * (height - 1);
    int new_y2 = height - new_y - 1;
	int index = 0;
	index += new_y2 * width;
	index += new_x;
    return color.at(index);
}