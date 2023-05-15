#include "tgaimage.h"

constexpr int width = 800;
constexpr int height = 800; 

int main(int argc, char** argc)
{
	TGAImage framebuffer(width, height, TGAImage::RGB);


	framebuffer.write_tga_file("framebuffer.tga");
	return 0;	
}
