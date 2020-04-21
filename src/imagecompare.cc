#include "imagecompare.h"

#include "compare.h"

constexpr auto FILTER_NAME{ "Name" };
constexpr auto ROI{ "Roi" };

ImageCompare::ImageCompare(QJsonObject const &a_config)
{
  m_subtractor = new Compare::None();
}

ImageCompare::~ImageCompare()
{
  delete m_subtractor;
}

void ImageCompare::configure(QJsonObject const &a_config)
{
  // qDebug()  << a_config << endl;
  auto const NAME_STRING{ a_config[FILTER_NAME].toString().toStdString() };
  auto const ROI_STRING{ a_config[ROI].toString().toStdString() };
  auto const DRON{ a_config["DronSize"].toString().toStdString() };
  auto const NAME_SID{ SID(NAME_STRING.c_str()) };
  H_Logger->trace("ImageCompare type: {} roi:{}", NAME_STRING, ROI_STRING);
  delete m_subtractor;
  H_Logger->trace("ImageCompare DronSize:{}", DRON);

  switch (NAME_SID)
  {
    case SID("CodeStats2014"): m_subtractor = { new Compare::CodeStats2014{ a_config } }; break;
    case SID("None"): m_subtractor = { new Compare::None() }; break;
    default: H_Logger->error("Unsupported compare type: {}", NAME_STRING); break;
  }
}

struct imageErrors ImageCompare::process(const cv::Mat_<uchar> &binary, const cv::Mat_<uchar> &gt)
{
  H_Logger->trace("ImageCompare::process()");
  m_timer.start();
  struct imageErrors temp_imageErrors = m_subtractor->process(binary, gt);
  m_timer.stop();
  H_Logger->trace("ImageCompare::process() done");
  return temp_imageErrors;
}

double ImageCompare::getElapsedTimeCompare()
{
  return m_timer.getTimeMilli();
}
