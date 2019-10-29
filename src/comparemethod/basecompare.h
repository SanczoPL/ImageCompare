#ifndef BASE_COMPARE_H
#define BASE_COMPARE_H

#include "../../../includeSpdlog/include/includeSpdlog.h"
#include <QtCore>
#include <opencv2/imgproc.hpp>

struct imageErrors
{
  quint32 tpError;
  quint32 fpError;
  quint32 fnError;
  quint32 tnError;
  quint32 nbShadowError;
};

class BaseCompare
{
 public:
  BaseCompare();
  virtual ~BaseCompare();

  virtual struct imageErrors process(const cv::Mat_<uchar> &binary, const cv::Mat_<uchar> &gt) = 0;
};

#endif // BASE_COMPARE_H
