/*
Ϊʲôʹ�þ���任����Ϊ���������ǰ�ˣ�Ȼ��ϲ���һ����������ʾ��α任�ĺ�
ƽ�Ʋ������Ա任������ʹ��������꣺�൱����������ά�ռ������������Ա任��������ƽ��z=1�Ͻ��У����z=1���ƽ��ͶӰ��2d������ƽ����
*/

#include "geometry.h"


const int depth = 255;

Matrix viewport(int x, int y, int w, int h);
Vec3f m2v(Matrix m);
Matrix v2m(Vec3f v);