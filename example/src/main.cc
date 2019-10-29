#include <imagecompare.h>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <chrono>
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
													 {"Roi", "/media/data/raw_video/snowFall/ROI.bmp"}};

	QJsonArray filters{filterConfig};

	qDebug() << "filters" << filters;

	ImageCompare imageCompare{filters};

	cv::VideoCapture cap1;
	cv::VideoCapture cap2;
	// cap.open(0);
	cap1.open("/media/data/raw_video/snowFall/input/in%06d.jpg");
	cap2.open("/media/data/raw_video/snowFall/groundtruth/gt%06d.png");
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
	cv::cvtColor(gt, gt, 6);
	cv::cvtColor(frame, frame, 6);
	cv::threshold(frame, frame, 100, 255, 0);
	cv::TickMeter tm;
	tm.reset();
	imageErrors errors2;
	for (int i = 0; i < 1000; i++) {
		cap1 >> frame;
		cap2 >> gt;
	}

	for (int i = 0; i < 2000; i++) {
		errors2.fnError = 0;
		errors2.fpError = 0;
		errors2.tnError = 0;
		errors2.tpError = 0;
		errors2.nbShadowError = 0;

		cap1 >> frame;
		cap2 >> gt;
		cv::cvtColor(gt, gt, 6);
		cv::cvtColor(frame, frame, 6);
		cv::threshold(frame, frame, 110, 255, 0);

		if (frame.empty()) break;
		if (gt.empty()) break;
		// frame = gt.clone();
		frame.at<uchar>(125, 125) = 255;
		frame.at<uchar>(125, 126) = 50;
		frame.at<uchar>(125, 127) = 170;
		// cv::circle(frame, cv::Point(125, 125), 5, 255, 1);

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
