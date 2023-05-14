#include "DrawLine.h"
#include "tgaimage.h"
#include "geometry.h"
#include "z_buffer.h"
#include "model.h"
#include <vector>
#include <cmath>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const int width = 800;
const int height = 800;
Model* model = NULL;
const Vec3f light_dir{ 0,0,-1 }; // light source

Vec3f world2screen(Vec3f v) {
    return Vec3f(int((v.x + 1.) * width / 2. + .5), int((v.y + 1.) * height / 2. + .5), v.z);
}

int main(int argc, char** argv) {
    if (2 == argc) {
        model = new Model(argv[1]);
    }
    else {
        model = new Model("obj/african_head/african_head.obj");
    }

    float* zbuffer = new float[width * height];
    for (int i = width * height; i--; zbuffer[i] = -std::numeric_limits<float>::max());

    TGAImage image(width, height, TGAImage::RGB);

    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for (int j = 0; j < 3; j++) {
            Vec3f v = model->vert(face[j]);
            screen_coords[j] = Vec2i((v.x + 1.) * width / 2., (v.y + 1.) * height / 2.);
            world_coords[j] = v;
        }
        Vec3f n = cross((world_coords[2] - world_coords[0]), (world_coords[1] - world_coords[0]));
        n.normalize();
        float intensity = n * light_dir;
        if (intensity > 0) {
            Vec3f pts[3];
            for (int i = 0; i < 3; i++) pts[i] = world2screen(model->vert(face[i]));
            triangle(pts, zbuffer, image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
        }
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}