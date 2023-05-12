#include "DrawLine.h"
#include "tgaimage.h"

const TGAColor white = TGAColor(255,255,255,255);
const TGAColor red = TGAColor(255,0,0,255);

int main()
{
    TGAImage image(100, 100, TGAImage::RGB);
    line2(13,20,80,40,image,white);
    line2(20,13,40,80,image,red);
    line2(80,40,13,20,image,red);
    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}