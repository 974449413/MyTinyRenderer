/*
为什么使用矩阵变换，因为矩阵可以提前乘，然后合并成一个矩阵，它表示多次变换的和
平移不是线性变换，我们使用齐次坐标：相当于我们在三维空间进行了这个线性变换，其中在平面z=1上进行，最后将z=1这个平面投影到2d的物理平面上
*/

#include "geometry.h"


const int depth = 255;

Matrix viewport(int x, int y, int w, int h);
Vec3f m2v(Matrix m);
Matrix v2m(Vec3f v);