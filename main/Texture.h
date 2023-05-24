#pragma once
#include "TGA.h"

class Texture{
public:
    Texture(const char* file_name);
    Eigen::Vector3i GetColor(float x, float y) const;
    void UncompressRLE(std::ifstream& in, std::uint8_t* data, const unsigned long& length);
private:
    std::vector<Eigen::Vector3i> color;
    std::uint16_t width;
	std::uint16_t height;
};