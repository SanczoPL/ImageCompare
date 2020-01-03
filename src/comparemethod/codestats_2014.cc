#include "codestats_2014.h"
#include <QJsonObject>

constexpr auto ROI{ "Roi" };
constexpr auto HEIGHT{ "Height" };
constexpr auto DRONSIZE{ "DronSize" };
constexpr auto WIDTH{ "Width" };


Compare::CodeStats2014::CodeStats2014(QJsonObject const &a_config)
{
  m_ROI = cv::imread({ a_config[ROI].toString().toStdString() }, 0);
  quint32 m_width = a_config[WIDTH].toInt();
  quint32 m_height = a_config[HEIGHT].toInt();
  quint32 m_dronSize = a_config[DRONSIZE].toInt();
  m_res = ( m_width * m_height  - dronSize) / m_dronSize;                         
}


struct imageErrors Compare::CodeStats2014::process(const cv::Mat_<uchar> &binary, const cv::Mat_<uchar> &gt)
{
  H_Logger->trace("imageErrors Compare::CodeStats2014::process()");
  if (m_ROI.empty())
  {
    H_Logger->error("m_ROI frame is null. Probably a bad path or incomplete folder.\n");
  }

  cv::MatConstIterator_<uchar> itBinary = binary.begin();
  cv::MatConstIterator_<uchar> itGT = gt.begin();
  cv::MatConstIterator_<uchar> itROI = m_ROI.begin();
  H_Logger->trace("imageErrors Compare::CodeStats2014::process() imageErrors");
  struct imageErrors m_errors2;
  m_errors2.fnError = 0;
  m_errors2.fpError = 0;
  m_errors2.tnError = 0;
  m_errors2.tpError = 0;
  m_errors2.nbShadowError = 0;
  H_Logger->trace("imageErrors Compare::CodeStats2014 Main loop: m_res:{}",m_res);
  cv::MatConstIterator_<uchar> itEnd = binary.end();
  for (; itBinary != itEnd; ++itBinary, ++itGT, ++itROI)
  {
    // Current pixel needs to be in the ROI && it must not be an unknown color
    if (*itROI != BLACK && *itGT != UNKNOWN)
    {
      if (*itBinary == WHITE)
      { // Model thinks pixel is background 
        if (*itGT == WHITE)
        {
          //++m_errors2.tpError; // and it is
          ++m_errors2.tpError;
        }
        else
        {
          //++m_errors2.fpError; // but it's not
          ++m_errors2.fpError;
        }
      }
      else
      { // Model thinks pixel is foreground
        if (*itGT == WHITE)
        {
          m_errors2.fnError+=m_res; // but it's not
        }
        else
        {
          m_errors2.tnError+=m_res; // and it is
        }
      }

      if (*itGT == SHADOW)
      {
        if (*itBinary == WHITE)
        {
          ++m_errors2.nbShadowError;
        }
      }
    }
  }
  H_Logger->trace("imageErrors Compare::CodeStats2014 done");
  return m_errors2;
}
