#ifndef NONE_H
#define NONE_H

#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include "basecompare.h"

class QJsonObject;

namespace Compare
{
class None : public BaseCompare
{
 public:
  None();
  struct imageErrors process(const cv::Mat_<uchar> &binary, const cv::Mat_<uchar> &gt);

 private:
};
} // namespace Compare

#endif // NONE_H
