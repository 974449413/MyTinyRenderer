#include "DrawLine.h"
//Bresenham's draw line algorithm

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) 
{
    line5(x0, y0, x1, y1, image, color);
}


//方案一：参数每次增加固定的量，相当于百分比增加；
//问题：精度问题，每次参数t增加的量无法保证
void line1(const int& x0,const int& y0,const int& x1,const int& y1, TGAImage& image, TGAColor color)
{
    for(float t=0.; t<=1; t += .01)
    {
        int x = x0 + (x1 - x0) * t;
        int y = y0 + (y1 - y0) * t;
        image.set(x, y, color);
    }
}

//方案二：按照x，每次增加1，然后y按照这个比例增加
//保证了以像素为单位进行增加
//问题：它的x只能增加，所以只有第二个点在第一个点的右方时才能绘制
//问题：没有考虑y值无法跟随x的情况，即y算出来是小数
//这步就是只绘制了第一象限按顺序的线
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

//1.保证x的增量大于等于y的增量，这样通过控制x每次+1，就更细腻;如果x增量小于y，x每次加一，y就不仅仅是加一了：斜率小于1
//2.保证x从小的向大的增加：斜率大于0
//本质：将任何线段，转换为从左到右，斜率为1的线进行计算
//如果斜率不合适，即大于1，就把它沿y=x进行对称
//如果是从右至左绘制的，就修改一下绘制顺序
//如果y=x对称了，在着色的时候，就再把y和x互换一下，保证正确
void line3(int x0,int y0,int x1,int y1, TGAImage& image, TGAColor color)
{
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { // if the line is steep, we transpose the image 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { // make it left−to−right 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    for (int x=x0; x<=x1; x++) { 
        float t = (x-x0)/(float)(x1-x0); 
        int y = y0*(1.-t) + y1*t; 
        if (steep) { 
            image.set(y, x, color); // if transposed, de−transpose 
        } else { 
            image.set(x, y, color); 
        } 
    } 
}

//上述代码的效率并不高，所以需要进行优化一下
//优化点在于计算t和根据t计算y坐标的地方
//上述代码的问题在于计算y坐标时，如果是小数会被强制归0
//下面代码通过斜率，得到了每次x增加1时，y的增量。如果y的小数部分累计增量大于了0.5，则会直接向上进1，即四舍五入
//如果进了1，就再减去1，保证之后的y值增加会弥补这个空缺
//误差很小，基本不影响显示
//主要是因为在循环中，上一个DDA算法在执行浮点数计算，而这个Bresenham算法在执行整数计算，所以效率会提升很大
//即Bresenham中点算法
void line4(int x0,int y0,int x1,int y1, TGAImage& image, TGAColor color)
{
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    float derror = std::abs(dy/float(dx)); 
    float error = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error += derror; 
        if (error>.5) { 
            y += (y1>y0?1:-1); 
            error -= 1.; 
        } 
    } 
}


//将所有操作都转换为整数
//消除所有浮点数，更加迅速
void line5(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) 
{ 
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
} 
