#ifndef IMAGE_COMPARE_H
#define IMAGE_COMPARE_H

#include <opencv2/imgproc.hpp>

class BaseCompare;
class QJsonArray;
namespace cv {
class Mat;
class TickMeter;
}  // namespace cv
struct imageErrors;

class ImageCompare {
 public:
	ImageCompare(QJsonArray const &a_subtractorConfiguration);
	~ImageCompare();

  void configure(QJsonArray const &a_subtractorConfiguration);
	struct imageErrors process(const cv::Mat_<uchar> &binary,
														 const cv::Mat_<uchar> &gt);
	double getElapsedTimeCompare();

 private:
	BaseCompare *m_subtractor{};
  cv::TickMeter m_timer;
};

#endif  // IMAGE_COMPARE_H
