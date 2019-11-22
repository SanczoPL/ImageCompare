#include "none.h"

Compare::None::None(QJsonObject const &a_config)
{
    H_Logger->trace("imageErrors Compare::None()");
} 

struct imageErrors Compare::None::process(const cv::Mat_<uchar> &binary, const cv::Mat_<uchar> &gt)
{
    H_Logger->trace("imageErrors Compare::None::process()");
    struct imageErrors m_errors2;
    return m_errors2;
}
