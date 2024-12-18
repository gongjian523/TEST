// OpenCV.Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <vector>

void Jpegcompress(const cv::Mat& src, cv::Mat& dest, int quality)
{
	std::vector<uchar> buff;
	std::vector<int> params;
	/*IMWRITE_JPEG_QUALITY For JPEG, it can be a quality from 0 to 100
	(the higher is the better). Default value is 95 */
	params.push_back(cv::IMWRITE_JPEG_QUALITY);
	params.push_back(quality);
	////将图像压缩编码到缓冲流区域
	//cv::imencode(".jpg", src, buff, params);
	////将压缩后的缓冲流内容解码为Mat，进行后续的处理
	//dest = cv::imdecode(buff, -1);
	//cv::imshow("src", src);
	//cv::imshow("dst", dest);
	cv::imwrite("E:\\转辙机数据\\20231024\\00-07-32-86-76-76天回镇采样机1号\\过车记录\\001635\\电机\\图像C.jpg", src, params);
}

int main()
{
	std::string fileName = "E:\\转辙机数据\\20231024\\00-07-32-86-76-76天回镇采样机1号\\过车记录\\001635\\电机\\图像.jpg";
	cv::Mat src = cv::imread(fileName, -1);
	if (src.empty())
	{
		std::cerr << " image open error!\n";
		return 0;
	}
	cv::Mat dest;
	//质量等级为设为50
	Jpegcompress(src, dest, 10);

	//cv2.IMWRITE_JPEG_QUALITY类型为 long ,必须转换成 int
	//cv2.IMWRITE_PNG_COMPRESSION, 从0到9 压缩级别越高图像越小。
	//std::vector<int> params;
	///*IMWRITE_JPEG_QUALITY For JPEG, it can be a quality from 0 to 100
	//(the higher is the better). Default value is 95 */
	//params.push_back(cv::IMWRITE_JPEG_QUALITY);
	//params.push_back(98);

	//cv::imwrite("1.jpg", src, params);
	////cv::imwrite('1.png',src, [int(cv::IMWRITE_PNG_COMPRESSION), 9])

	getchar();
	return 0;
}



