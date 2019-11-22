#ifndef IMAGE_COMPARE_H
#define IMAGE_COMPARE_H

#include <opencv2/imgproc.hpp>
#include <QJsonObject>

class BaseCompare;
class QJsonArray;
namespace cv {
class Mat;
class TickMeter;
}  // namespace cv
struct imageErrors;

class ImageCompare {
 public:
	ImageCompare(QJsonObject const &a_config);
	~ImageCompare();

  void configure(QJsonObject const &a_config);
	struct imageErrors process(const cv::Mat_<uchar> &binary,
														 const cv::Mat_<uchar> &gt);
	double getElapsedTimeCompare();

 private:
	BaseCompare *m_subtractor{};
  cv::TickMeter m_timer;
};

#endif  // IMAGE_COMPARE_H
