#include "../include/imagecompare.h"

#include "compare.h"

constexpr auto FILTER_NAME{ "Name" };

ImageCompare::ImageCompare(QJsonObject const &a_config)
{
  configure(a_config);
}

ImageCompare::~ImageCompare()
{
  delete m_subtractor;
}

void ImageCompare::configure(QJsonObject const &a_config)
{
  delete m_subtractor;

  auto const NAME_STRING{ a_config[FILTER_NAME].toString().toStdString() };
  auto const NAME_SID{ SID(NAME_STRING.c_str()) };

  switch (NAME_SID)
  {
    case SID("CodeStats2014"): m_subtractor = { new Compare::CodeStats2014{a_config} }; break;
    default: H_Logger->error("Unsupported filter type: {}", NAME_STRING); break;
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
