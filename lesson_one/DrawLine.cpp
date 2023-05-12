#include "DrawLine.h"
//Bresenham's draw line algorithm

//first:rely on t's frequency
void line1(const int& x0,const int& y0,const int& x1,const int& y1, TGAImage& image, TGAColor color)
{
    for(float t=0.; t<=1; t += .01)
    {
        int x = x0 + (x1 - x0) * t;
        int y = y0 + (y1 - y0) * t;
        image.set(x, y, color);
    }
}

//second:make sure every time x add 1
//but this function can not draw with reverse line,because x is to x1 from x0 with addition
void line2(const int& x0,const int& y0,const int& x1,const int& y1, TGAImage& image, TGAColor color)
{
    for(int x = x0;x<=x1;++x)
    {
        float t = (x-x0) / (float)(x1-x0);
        //int y = y0 * (1.-t) + y1 * t;
        int y = y0 + (y1 - y0) * t;
        image.set(x, y, color);
    }
}