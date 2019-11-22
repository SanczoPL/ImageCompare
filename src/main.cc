#include "imagecompare.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include "../../../IncludeSpdlog/spdlog.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define floatqDebug() qDebug() << fixed << qSetRealNumberPrecision(2)
struct imageErrors {
	quint32 tpError;
	quint32 fpError;
	quint32 fnError;
	quint32 tnError;
	quint32 nbShadowError;
};

int main() {
	QJsonObject filterConfig{{"Name", "CodeStats2014"},
							{"Roi", "/media/data/genetic/Dron3/ROI.bmp"}};
							
	H_Logger->set_level(static_cast<spdlog::level::level_enum>(0));
	H_Logger->set_pattern("[%Y-%m-%d] [%H:%M:%S.%e] [%t] [%^%l%$] %v");
	H_Logger->debug("start main logger with LogLevel:{}",0);
	ImageCompare imageCompare{filterConfig};

	cv::VideoCapture cap1;
	cv::VideoCapture cap2;
	// cap.open(0);
	//"FolderInput":"/media/data/genetic/Dron3/",
	//		"VideoInput":"input/%d.png",
	//		"VideoGT":"groundtruth/%d.png",

	cap1.open("/media/data/genetic/Dron3/input/%d.png");
	cap2.open("/media/data/genetic/Dron3/groundtruth/%d.png");
	if (!cap1.isOpened()) {
		return -1;
	}
	if (!cap2.isOpened()) {
		return -1;
	}
	cv::Mat frame;
	cv::Mat gt;
	cap1 >> frame;
	cap2 >> gt;

	if (frame.empty()) 
	{
		floatqDebug() << "frame empty";
		return -1;
	}
	if (gt.empty()) 
	{
		floatqDebug() << "gt empty";
		return -1;
	}

	if(frame.channels() == 3)
	{
		
		cv::cvtColor(frame, frame, 6);
	}
	if(gt.channels() == 3)
	{
	cv::cvtColor(gt, gt, 6);
	}
	
	
	
	cv::threshold(frame, frame, 100, 255, 0);
	cv::TickMeter tm;
	tm.reset();

	imageErrors errors2;
	/*
	for (int i = 0; i < 200; i++) {
		cap1 >> frame;
		cap2 >> gt;
	}*/

	for (int i = 0; i < 200; i++) {
		errors2.fnError = 0;
		errors2.fpError = 0;
		errors2.tnError = 0;
		errors2.tpError = 0;
		errors2.nbShadowError = 0;

		cap1 >> frame;
		cap2 >> gt;
		if(frame.channels() == 3)
		{
		cv::cvtColor(frame, frame, 6);
		}
		if(gt.channels() == 3)
		{
		cv::cvtColor(gt, gt, 6);
		}
		cv::threshold(frame, frame, 110, 255, 0);

		if (frame.empty()) break;
		if (gt.empty()) break;
		// frame = gt.clone();
		//frame.at<uchar>(125, 125) = 255;
		//frame.at<uchar>(125, 126) = 50;
		//frame.at<uchar>(125, 127) = 170;
		// cv::circle(frame, cv::Point(125, 125), 5, 255, 1);
		floatqDebug() << "i:" << i;
		errors2 = imageCompare.process(frame, gt);
		floatqDebug() << "i:" << i;
		floatqDebug() << "fnError:" << errors2.fnError;
		floatqDebug() << "fpError:" << errors2.fpError;
		floatqDebug() << "tnError:" << errors2.tnError;
		floatqDebug() << "tpError:" << errors2.tpError;
		floatqDebug() << "nbShadowError:" << errors2.nbShadowError;

		cv::imshow("Before", frame);
		cv::imshow("gt", gt);
		cv::waitKey(0);
	}

	return 0;
}
