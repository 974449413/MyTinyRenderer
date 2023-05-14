#ifndef __MY_TRIANGLE__
#define __MY_TRIANGLE__
#include "geometry.h"
#include "tgaimage.h"
#include <vector>
#include <algorithm>


const TGAColor white = TGAColor(255,255,255,255);
const TGAColor red = TGAColor(255,0,0,255);
const TGAColor green = TGAColor(0,255,0,255);



void triangle_base(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color);
void triangle_compose(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color);
void triangle_box(Vec2i* pts, TGAImage &image, TGAColor color);
Vec3f barycentric(Vec2i *pts, Vec2i P);















#endif