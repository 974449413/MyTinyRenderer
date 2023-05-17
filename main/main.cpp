#include <opencv2/opencv.hpp>

int main()
{
	cv::Mat image(700, 700, CV_32FC3);
	image.convertTo(image, CV_8UC3, 1.0f);
	cv::Mat image2(700, 700, CV_8UC3, cv::Scalar(0, 0, 0));
	while (true)
	{
		/*for (int i = 0; i < image2.cols; ++i)
		{
			image2.at<cv::Vec3b>(i, i) = cv::Vec3b(255, 0, 0);
		}*/
		//image2.at<cv::Vec3b>(350, 350) = cv::Vec3b(255, 0, 0);
		cv::imshow("dcr", image2);
		cv::waitKey(10);
	}
	return 0;
}