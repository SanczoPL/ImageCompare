#ifndef NONE_H
#define NONE_H

#include "basecompare.h"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

class QJsonObject;

namespace Compare {
class None : public BaseCompare {
 public:
	None(QJsonObject const &a_config);
	struct imageErrors process(const cv::Mat_<uchar> &binary,
														 const cv::Mat_<uchar> &gt);


 private:
};
} // namespace Compare

#endif // NONE_H
