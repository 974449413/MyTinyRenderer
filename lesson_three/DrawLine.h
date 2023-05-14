#ifndef __DrawLine__
#define __DrawLine__
#include "tgaimage.h"
#include "geometry.h"
void line1(const int& x0,const int& y0,const int& x1,const int& y1, TGAImage& image, TGAColor color);
void line2(const int& x0,const int& y0,const int& x1,const int& y1, TGAImage& image, TGAColor color);
void line3(int x0,int y0,int x1,int y1, TGAImage& image, TGAColor color);
void line4(int x0,int y0,int x1,int y1, TGAImage& image, TGAColor color);
void line5(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);
void line(Vec2i a, Vec2i b, TGAImage& image, TGAColor color);
















#endif