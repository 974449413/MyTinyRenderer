/*lesson_one提供的画线代码只能勾勾勒出一个三角形的轮廓，但是无法绘制实心的三角形*/
/*
1.快速
2.不依赖传递顶点的顺序，即传递的顶点顺序可以是随机的
3.两个三角形如果有共享顶点时，由于舍入误差的存在，它们的边界不一定会完全的重合。所以应该确保三角形在公共顶点完全重合，没有空隙。
*/

#include "triangle.h"
#include "model.h"

Model* model = NULL;
const int width = 800;
const int height = 800;
const Vec3f light_dir{ 0,0,-1 }; // light source

int main(int argc, char** argv)
{
    if (2 == argc) {
        model = new Model(argv[1]);
    }
    else {
        model = new Model("f:/game/mytinyrenderer/debug/obj/african_head/african_head.obj");
    }
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
            triangle_box(screen_coords, image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
        }
    }

    /*
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        for (int j = 0; j < 3; j++) {
            Vec3f world_coords = model->vert(face[j]);
            screen_coords[j] = Vec2i((world_coords.x + 1.) * width / 2., (world_coords.y + 1.) * height / 2.);
        }
        triangle_box(screen_coords, image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
    }*/

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");

    return 0;
}