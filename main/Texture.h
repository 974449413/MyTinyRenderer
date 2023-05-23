#include "TGA.h"

class Texture{
public:
    Texture(const char* file_name);
    Eigen::Vector3i GetColor(float x, float y);
    void UncompressRLE(std::ifstream& in, std::uint8_t* data, const unsigned long& length);
    std::vector<Eigen::Vector3i> color;
private:
    
    std::uint16_t width;
	std::uint16_t height;
};