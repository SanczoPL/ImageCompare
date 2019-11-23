#include "../include/imagecompare.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include "compare.h"

constexpr auto FILTER_NAME{ "Name" };

ImageCompare::ImageCompare(QJsonArray const &a_subtractorConfiguration)
{
  configure(a_subtractorConfiguration);
}

ImageCompare::~ImageCompare()
{
  delete m_subtractor;
}

void ImageCompare::configure(QJsonArray const &a_subtractorConfiguration)
{
  delete m_subtractor;
  // qDebug() << "ImageCompare:" << a_subtractorConfiguration << endl;
  for (auto const &SUBTRACTOR_CONFIG : a_subtractorConfiguration)
  {
    auto const NAME_STRING{ SUBTRACTOR_CONFIG[FILTER_NAME].toString().toStdString() };
    auto const NAME_SID{ SID(NAME_STRING.c_str()) };

    switch (NAME_SID)
    {
      case SID("CodeStats2014"): m_subtractor = { new Compare::CodeStats2014{ SUBTRACTOR_CONFIG.toObject() } }; break;
      default: H_Logger->error("Unsupported filter type: {}", NAME_STRING); break;
    }
  }
}

struct imageErrors ImageCompare::process(const cv::Mat_<uchar> &binary, const cv::Mat_<uchar> &gt)
{
  m_timer.start();

  struct imageErrors temp_imageErrors = m_subtractor->process(binary, gt);
  m_timer.stop();
  return temp_imageErrors;
}

double ImageCompare::getElapsedTimeCompare()
{
  return m_timer.getTimeMilli();
}
