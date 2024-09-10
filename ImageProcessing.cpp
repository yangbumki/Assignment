#include "pch.h"
#include "ImageProcessing.h"

using namespace cv;
using namespace std;

#define IMAGE_RECT_OFFSET		6

ImageProcessing::ImageProcessing() {
}

ImageProcessing::~ImageProcessing() {

}
void ImageProcessing::WarningMessage(std::string msg) {
	cout << "===IMAGE_PROCESSING=== \n";
	cout << msg << endl;
}

cv::Mat ImageProcessing::to_mat(void* src, const SIZE& size,const int pitch) {
	Mat img(cv::Size{ size.cx, size.cy }, CV_8UC1, src, pitch);

	if (img.empty()) {
		WarningMessage("Failed to convert mat");
		return Mat{};
	}

	return img.clone();
}

bool ImageProcessing::to_CImage(cv::Mat& src, CImage& dst) {
	int type = src.type();
	int channels = src.channels();

	if (channels == 3 && (type == CV_8UC3 || type == CV_8UC1)) {
		dst.Create(src.cols, src.rows, 8*channels);

		for (int y = 0; y < src.rows; y++) {
			for (int x = 0; x < src.cols; x++) {
				cv::Vec3b color = src.at<cv::Vec3b>(y, x);

				BYTE r = color[2];
				BYTE g = color[1];
				BYTE b = color[0];

				dst.SetPixel(x, y, RGB(r, g, b));
			}
		}
	}
	else
		return false;

	return true;
}

ObjectInfo ImageProcessing::FindObjectPos(CImage& src) {
	image = to_mat(src.GetBits(), SIZE{ src.GetWidth(), src.GetHeight() }, src.GetPitch());
	if (image.empty()) {
		cerr << "Failed to mat image \n";
		return ObjectInfo{};
	}

	vector<byte> xPos{};

	for (int row = 0; row < image.rows; row++) {
		for (int col = 0; col < image.cols; col++) {
			image.at<uchar>(row, col) == 255 ? xPos.push_back(col) : NULL;
		}
	}

	std::sort(xPos.begin(), xPos.end());
	unsigned int radius = (xPos.at(xPos.size() - 1) - xPos.at(0))/2;
	
	Mat labels{}, stats{}, centroids{};
	int cnt = connectedComponentsWithStats(image, labels, stats, centroids);

	ObjectInfo oi{};


	RECT rect {};

	rect.left = stats.ptr<int>(1)[0];
	rect.top = stats.ptr<int>(1)[1];
	rect.right = stats.ptr<int>(1)[0] + stats.ptr<int>(1)[2];
	rect.bottom = stats.ptr<int>(1)[1] + stats.ptr<int>(1)[3];

	oi.rect = rect;
	oi.centerPoint.x = static_cast<int>(centroids.ptr<double>(1)[0]);
	oi.centerPoint.y = static_cast<int>(centroids.ptr<double>(1)[1]);

	return oi;
}

//void* ImageProcessing::GetAnalyzedCircle(CImage& src) {
//	/*RECT objInfo = FindObjectPos(src);
//	
//	unsigned int radius = (objPosRect.right - objPosRect.left) / 2;
//	
//	POINT centerPoint{ objPosRect.left + radius, objPosRect.top + radius };*/
//
//	auto objInfo = FindObjectPos(src);
//
//	unsigned int radius = (objInfo.rect.right - objInfo.rect.left) / 2;
//
//	POINT centerPoint{ objInfo.centerPoint.x, objInfo.centerPoint.y };
//
//	//to_mat 함수로 image 맴버변수 값 채워짐
//	if (image.empty()) {
//		cerr << "Faield to convert mat \n";
//		return nullptr;
//	}
//
//	//원 중점 x 표시
//	image.at<uchar>(centerPoint.y, centerPoint.x) = 0;
//	image.at<uchar>(centerPoint.y - 1, centerPoint.x + 1) = 0;
//	image.at<uchar>(centerPoint.y - 1, centerPoint.x - 1) = 0;
//	image.at<uchar>(centerPoint.y + 1, centerPoint.x + 1) = 0;
//	image.at<uchar>(centerPoint.y + 1, centerPoint.x - 1) = 0;
//
//	//안내선 표시
//	for (int row = 0; row <= centerPoint.y; row++) 
//		image.at<uchar>(row, centerPoint.x) = 128;
//
//	for (int col = 0; col <= centerPoint.x; col++)
//		image.at<uchar>(centerPoint.y, col) = 128;
//
//	/*Mat colorImage{};
//
//	cvtColor(image, colorImage, COLOR_GRAY2BGR);
//
//	POINT startPoint{ objInfo.rect.left, objInfo.rect.top };
//	POINT currentPoint = startPoint;
//
//	while (1) {
//		if (currentPoint.x == centerPoint.x && currentPoint.y == centerPoint.y) {
//			break;
//		}
//
//		if (radius >= sqrt(pow(abs(currentPoint.x++ - centerPoint.x), 2) + pow(abs(currentPoint.y++ - centerPoint.y), 2))) {
//			colorImage.at<Vec3b>(currentPoint.y - 1, currentPoint.x - 1) = Vec3b{ 0, 0, 255 };
//		}
//	}
//
//	return colorImage.data;*/
//
//	return image.data;
//}

bool ImageProcessing::GetAnalyzedCircle(CImage& src, CImage& dst) {
	/*RECT objInfo = FindObjectPos(src);

	unsigned int radius = (objPosRect.right - objPosRect.left) / 2;

	POINT centerPoint{ objPosRect.left + radius, objPosRect.top + radius };*/

	auto objInfo = FindObjectPos(src);

	unsigned int radius = (objInfo.rect.right - objInfo.rect.left) / 2;

	POINT centerPoint{ objInfo.centerPoint.x, objInfo.centerPoint.y };

	//to_mat 함수로 image 맴버변수 값 채워짐
	if (image.empty()) {
		cerr << "Faield to convert mat \n";
		return false;
	}

	//원 중점 x 표시
	image.at<uchar>(centerPoint.y, centerPoint.x) = 0;
	image.at<uchar>(centerPoint.y - 1, centerPoint.x + 1) = 0;
	image.at<uchar>(centerPoint.y - 1, centerPoint.x - 1) = 0;
	image.at<uchar>(centerPoint.y + 1, centerPoint.x + 1) = 0;
	image.at<uchar>(centerPoint.y + 1, centerPoint.x - 1) = 0;

	//안내선 표시
	for (int row = 0; row <= centerPoint.y; row++)
		image.at<uchar>(row, centerPoint.x) = 128;

	for (int col = 0; col <= centerPoint.x; col++)
		image.at<uchar>(centerPoint.y, col) = 128;

	Mat colorImage{};

	cvtColor(image, colorImage, COLOR_GRAY2BGR);

	POINT startPoint{ objInfo.rect.left, objInfo.rect.top };
	POINT currentPoint = startPoint;

	//최적화 필요
	while (1) {
		if (currentPoint.x == centerPoint.x && currentPoint.y == centerPoint.y) {
			break;
		}

		if (radius >= sqrt(pow(abs(currentPoint.x++ - centerPoint.x), 2) + pow(abs(currentPoint.y++ - centerPoint.y), 2))) {
			colorImage.at<Vec3b>(currentPoint.y - 1, currentPoint.x - 1) = Vec3b{ 0, 0, 255 };
		}
	}

	std::string radiusText("Radius : " + std::to_string(radius));
	std::string centerPtText("Center Point [ " + std::to_string(centerPoint.x) + " , " 
		+ std::to_string(centerPoint.y) + "]");

	putText(colorImage, radiusText, Point(0, src.GetHeight()-40), 0, 0.4, Scalar(0, 0, 255), 1);
	putText(colorImage, centerPtText, Point(0, src.GetHeight() - 20), 0, 0.4, Scalar(0, 255, 0), 1);

	if (!to_CImage(colorImage, dst)) {
		cerr << "Faield to convert CImage\n";
		return -1;
	}

	return true;
}