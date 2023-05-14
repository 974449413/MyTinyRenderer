#include "perspective.h"

//����һ����ά����������ת��Ϊ4ά��������꣬���е���ά����1.0
Matrix v2m(Vec3f v) {
    Matrix m(4, 1);
    m[0][0] = v.x;
    m[1][0] = v.y;
    m[2][0] = v.z;
    m[3][0] = 1.f;
    return m;
}

//����һ��������꣬����ת��Ϊ��ά�������������Ե���ά�ȵ�ֵ����
Vec3f m2v(Matrix m) {
    return Vec3f(m[0][0] / m[3][0], m[1][0] / m[3][0], m[2][0] / m[3][0]);
}

Matrix viewport(int x, int y, int w, int h) {
    //���ȣ�������һ����ά�ı任����
    Matrix m = Matrix::identity(4);
    m[0][3] = x + w / 2.f;
    m[1][3] = y + h / 2.f;
    m[2][3] = depth / 2.f;

    m[0][0] = w / 2.f;
    m[1][1] = h / 2.f;
    m[2][2] = depth / 2.f;
    return m;
}