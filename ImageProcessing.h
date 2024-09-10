#pragma once

typedef struct OBJECT_INFO {
	RECT rect;
	POINT centerPoint{};
}ObjectInfo;

class ImageProcessing {

private:
	cv::Mat image{};

	void WarningMessage(std::string msg);
	cv::Mat to_mat(void* src, const SIZE& size,const int pitch);
	bool to_CImage(cv::Mat& src, CImage& image);

public:
	ImageProcessing();
	~ImageProcessing();

	ObjectInfo FindObjectPos(CImage& src);
	/*void* GetAnalyzedCircle(CImage& src);*/
	bool ImageProcessing::GetAnalyzedCircle(CImage& src, CImage& dst);
};