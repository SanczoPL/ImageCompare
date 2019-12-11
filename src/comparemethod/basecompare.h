#ifndef BASE_COMPARE_H
#define BASE_COMPARE_H

#include "../../../../IncludeSpdlog/spdlog.h"
#include <QtCore>
#include <opencv2/imgproc.hpp>

struct imageErrors
{
  quint64 tpError;
  quint64 fpError;
  quint64 fnError;
  quint64 tnError;
  quint64 nbShadowError;
};

class BaseCompare
{
 public:
  BaseCompare();
  virtual ~BaseCompare();

  virtual struct imageErrors process(const cv::Mat_<uchar> &binary, const cv::Mat_<uchar> &gt) = 0;
};

#endif // BASE_COMPARE_H
