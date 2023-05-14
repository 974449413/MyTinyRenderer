#include "geometry.h"
#include "tgaimage.h"
#include <algorithm>

extern const int width;

void rasterize_yBuffer(Vec2i p0, Vec2i p1, TGAImage& image, TGAColor color, int ybuffer[]);
void triangle(Vec3f* pts, float* zbuffer, TGAImage& image, TGAColor color);