
#include "opencv2/opencv.hpp"

using namespace cv;


int main(int, char**)
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Mat image;
	namedWindow("Webcam", 1);
	namedWindow("Gray Webcam", 1);
	while(1)
	{
		Mat frame;
		Mat gray_image;
		cap >> frame; // get a new frame from camera
		cvtColor(frame, gray_image, COLOR_BGR2GRAY);
		line(frame, Point((frame.cols / 2) - 50, frame.rows / 2), Point((frame.cols/2) + 50, frame.rows / 2), Scalar(0,0,255), 1);
		line(frame, Point(frame.cols / 2, (frame.rows / 2) - 50), Point(frame.cols / 2, (frame.rows/2)+50), Scalar(0, 0, 255), 1);
		putText(frame, "TRISTAN IS FUCKING AWESOME!", cvPoint(30, 30),
			FONT_HERSHEY_SIMPLEX, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
		//GaussianBlur(image, image, Size(7, 7), 1.5, 1.5);
		//Canny(image, image, 0, 30, 3);
		imshow("Webcam", frame);
		imshow("Gray Webcam", gray_image);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
