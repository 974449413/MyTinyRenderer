#include<opencv2/opencv.hpp>
#include"Rasterizer.h"

constexpr int width = 700;
constexpr int height = 700; 

const Eigen::Vector3f eye_pos = { 0, 0, 5 };

constexpr float fov = 45;
constexpr float aspect_ratio = 1;
constexpr float z_near = 0.1;
constexpr float z_far = 50;

int main(int argc, char** argv)
{
	Rasterizer rasterizer(height, width);
	while (true) {
		rasterizer.SetModelTransformation();
		rasterizer.SetViewTransformation(eye_pos);
		rasterizer.SetPerspectiveTransformation(fov, aspect_ratio, z_near, z_far, true);
		rasterizer.SetViewportTransformation(height, width);

		rasterizer.DrawLine(Eigen::Vector2i{ 0, 0 }, Eigen::Vector2i{ 100, 200});
		/*rasterizer.DrawLine(Eigen::Vector2i{ 0, 2 }, Eigen::Vector2i{ 4, 0 });
		rasterizer.DrawLine(Eigen::Vector2i{ 4, 0 }, Eigen::Vector2i{ 2, 0 });*/
		//rasterizer.draw_line2(Eigen::Vector3f{ 0, 0, 0}, Eigen::Vector3f{ 50, 10, 0});
		/*cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
		image.convertTo(image, CV_8UC3, 1.0f);
		cv::imshow("image", image);*/
		cv::Mat image(height, width, CV_32FC3, rasterizer.GetFrameBuffer().data());	//cv表示opencv，8u表示每个像素占8位，C3表示3通道
		image.convertTo(image, CV_8UC3, 1.0f);
		cv::imshow("image", image);
		cv::waitKey(10);
	}
	
	return 0;	
}
