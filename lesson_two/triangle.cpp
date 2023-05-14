#include "triangle.h"


//这是一个老派的做法：扫线
void triangle_base(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color)
{
    // sort the vertices, t0, t1, t2 lower−to−upper (bubblesort yay!) 
    if (t0.y>t1.y) std::swap(t0, t1); 
    if (t0.y>t2.y) std::swap(t0, t2); 
    if (t1.y>t2.y) std::swap(t1, t2); 
    int total_height = t2.y-t0.y; 
    for (int y=t0.y; y<=t1.y; y++) { 
        //为了避免除以0，所以进行了+1
        //同时也会引入误差，即beta边会比alpha边低一点
        int segment_height = t1.y-t0.y+1; 
        float alpha = (float)(y-t0.y)/total_height; 
        float beta  = (float)(y-t0.y)/segment_height; // be careful with divisions by zero 
        Vec2i A = t0 + (t2-t0)*alpha; 
        Vec2i B = t0 + (t1-t0)*beta; 
        //保证了A点在B点的左边
        if (A.x>B.x) std::swap(A, B); 
        //从左向右，填充颜色
        for (int j=A.x; j<=B.x; j++) { 
            image.set(j, y, color); // attention, due to int casts t0.y+i != A.y 
        } 
    } 
    for (int y=t1.y; y<=t2.y; y++) { 
        //为了避免除以0，所以进行了+1
        //同时也会引入误差，即beta边会比alpha边低一点
        int segment_height = t2.y-t1.y+1; 
        float alpha = (float)(y-t0.y)/total_height; 
        float beta  = (float)(y-t1.y)/segment_height; // be careful with divisions by zero 
        Vec2i A = t0 + (t2-t0)*alpha; 
        Vec2i B = t1 + (t2-t1)*beta; 
        //保证了A点在B点的左边
        if (A.x>B.x) std::swap(A, B); 
        //从左向右，填充颜色
        for (int j=A.x; j<=B.x; j++) { 
            image.set(j, y, color); // attention, due to int casts t0.y+i != A.y 
        } 
    } 
}

//整合上面的行扫描代码
void triangle_compose(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color)
{
    //当三点在一条线上，退出
    if (t0.y==t1.y && t0.y==t2.y) return; // I dont care about degenerate triangles 
    // sort the vertices, t0, t1, t2 lower−to−upper (bubblesort yay!) 
    //交换顶点位置，使得从上到下依次是t2,t1,t0
    if (t0.y>t1.y) std::swap(t0, t1); 
    if (t0.y>t2.y) std::swap(t0, t2); 
    if (t1.y>t2.y) std::swap(t1, t2); 
    //得到总高度：total_height
    int total_height = t2.y-t0.y; 
    //这里i表示离t2.y的距离
    for (int i=0; i<total_height; i++) { 
        //如果下两个顶点一样高，或者扫描线增长到过了t1顶点的时候，second_half为true
        bool second_half = i>t1.y-t0.y || t1.y==t0.y; 
        //如果过了一半，就是t2.y-t1.y，否则就是还在绘制第一条线段，就是t1.y-t0.y
        int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y; 
        //依旧是总高度和半步高度的百分比
        float alpha = (float)i/total_height; 
        float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height; // be careful: with above conditions no division by zero here 
        Vec2i A =               t0 + (t2-t0)*alpha; 
        Vec2i B = second_half ? t1 + (t2-t1)*beta : t0 + (t1-t0)*beta; 
        if (A.x>B.x) std::swap(A, B); 
        for (int j=A.x; j<=B.x; j++) { 
            image.set(j, t0.y+i, color); // attention, due to int casts t0.y+i != A.y 
        } 
    } 
}

    

//基于包围盒，并遍历像素节点的方式
//1.要得到包围盒
//2.要进行重心坐标的计算，用于判断像素是否在三角形的内部

//重心坐标计算
Vec3f barycentric(Vec2i *pts, Vec2i P) 
{ 
    Vec3f u = cross(Vec3f(pts[2][0]-pts[0][0], pts[1][0]-pts[0][0], pts[0][0]-P[0]), Vec3f(pts[2][1]-pts[0][1], pts[1][1]-pts[0][1], pts[0][1]-P[1]));
    /* `pts` and `P` has integer value as coordinates
       so `abs(u[2])` < 1 means `u[2]` is 0, that means
       triangle is degenerate, in this case return something with negative coordinates */
    if (std::abs(u[2])<1) return Vec3f(-1,1,1);
    return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z); 
}

void triangle_box(Vec2i* pts, TGAImage &image, TGAColor color)
{
    //包围盒计算
    //最后bboxmin的就是左上角，bboxmax就是右下角
    //视图坐标系左上角是原点
    Vec2i bboxmin(image.get_width()-1,  image.get_height()-1); 
    Vec2i bboxmax(0, 0); 
    Vec2i clamp(image.get_width()-1, image.get_height()-1); 
    for (int i=0; i<3; i++) { 
        for (int j=0; j<2; j++) { 
            bboxmin[j] = std::max(0,        std::min(bboxmin[j], pts[i][j])); 
            bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], pts[i][j])); 
        } 
    } 
    //使用点P，来表示像素的坐标位置
    //返回得到的bc_screen是一个三维向量，表示重心坐标
    Vec2i P; 
    for (P.x=bboxmin.x; P.x<=bboxmax.x; P.x++) { 
        for (P.y=bboxmin.y; P.y<=bboxmax.y; P.y++) { 
            Vec3f bc_screen  = barycentric(pts, P); 
            //只要重心坐标有一个是小于0的，就说明它不在三角形内
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue; 
            image.set(P.x, P.y, color); 
        } 
    } 

}
