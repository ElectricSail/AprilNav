/**
* Originally created by Edwin Olson of University of Michigan
* Originally Ported to C++ by Jeffrey Boyland and David Touretzky of Carnegie Mellon University
* Updated by Michael Kaess of MIT
*
* Adapted by Tristan Schuler and Greta Studier of NASA MSFC for Electric Sail simulations
*
*
*
* Opens the first available camera (typically a built in camera in a
* laptop) and continuously detects April tags in the incoming
* images. Detections are both visualized in the live image and shown
* in the text console. Optionally allows selecting of a specific
* camera in case multiple ones are present and specifying image
* resolution as long as supported by the camera. Also includes the
* option to send tag detections via a serial port, for example when
* running on a Raspberry Pi that is connected to an Arduino.
*/

#define _USE_MATH_DEFINES

using namespace std;

#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <sys/time.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cmath>

#ifndef __APPLE__
#define EXPOSURE_CONTROL // only works in Linux
#endif

#ifdef EXPOSURE_CONTROL
#include <libv4l2.h>
#include <linux/videodev2.h>
#include <fcntl.h>
#include <errno.h>
#endif

// OpenCV library for easy access to USB camera and drawing of images
// on screen
#include "opencv2/opencv.hpp"

// April tags detector and various families that can be selected by command line option
#include "AprilTags/TagDetector.h"
#include "AprilTags/Tag16h5.h"
#include "AprilTags/Tag25h7.h"
#include "AprilTags/Tag25h9.h"
#include "AprilTags/Tag36h9.h"
#include "AprilTags/Tag36h11.h"

using namespace cv;

//Stores Tag information for Optimization

class TagOptimization {

public:
	int count;
	double time;
	int tagID;
	double X, Y, Z; //Meters
	double pitch, roll, yaw; //Radians
	double QR_X, QR_Y; // Meters
	double QR_Z = 8.1; //Meters 
	double CAMERA_X, CAMERA_Y, CAMERA_Z; //Meters
	double X_Rot, Y_Rot;

										 //Unique coordinate system, You must precisely measure the location of your coordinates in 3D space.
										 //The index of a coordinate applys to the tag id. Currently only accounts for [X,Y]
	double coordinates1[9][2] = { { 4.117,1.217 },{ 1.446,3.442 },{ 4.141,5.089 },{ 0,0 },{ 0,0 },{ 0,-.7 },{ 0,1 },{ 0,0 },{ 0,0 } };
	
	//Wall coordinates
	double coordinates[36][2] = { { 0,0 },{ -1.5,0 },{ 1.5,0 },{ 0,0 },{ 0,1 },{ 0,-.755 },{ 0,1 },{ 0,0 },{ 0,0 },{ 0,1 },{ 0,0 },{ 0,0 },{ 0,1 },{ 0,0 },{ 0,0 },{ 0,1 },{ 0,0 },{ 0,0 },{ 0,1 },{ 0,0 },{ 0,0 },{ 0,1 },{ 0,0 },{ 0,0 },{ 0,1 },{ 0,0 },{ 0,0 },{ 0,1 },{ 0,0 },{ 0,0 },{ 0,1 },{ 0,0 },{ 0,0 },{ 0,1 },{ 0,0 },{ 0,0 } };

	TagOptimization(double TIME, int TAGID, double x, double y, double PITCH, double ROLL, double YAW)
	{
		time = TIME;
		tagID = TAGID;
		X = x;
		Y = y;
		pitch = PITCH;
		roll = ROLL;
		yaw = YAW;
		//Determine QR's coordinates given ID
		QR_X = coordinates[tagID][0];
		QR_Y = coordinates[tagID][1];
		//Determine Camera Position in relation to QR Coordinate 
		//Coordinate System has to be rotated to account for orientation of camera
		X_Rot = X*cos(yaw) - Y*sin(yaw);
		Y_Rot = Y*cos(yaw) + X*sin(yaw);
		CAMERA_X = QR_X - X_Rot;
		CAMERA_Y = QR_Y - Y_Rot;
		//convert radians to degrees
		pitch = pitch * 180 / M_PI;
		roll = roll * 180 / M_PI;
		yaw = yaw * 180 / M_PI;
		
	}

	friend ostream& operator<<(ostream& os, const TagOptimization& t);
};

//Allows you to print a TagOptimization object using cout << 
ostream& operator<<(ostream& os, const TagOptimization& t)
{
	os << "," << t.time << "," << t.tagID << "," << t.X << "," << t.Y << ","
		<< t.pitch << "," << t.roll << "," << t.yaw << "," << t.X_Rot << "," << t.Y_Rot << ","
		<< t.CAMERA_X << "," << t.CAMERA_Y << "\n";
	return os;
}

const string usage = "\n"
"Usage:\n"
"  apriltags_demo [OPTION...] [IMG1 [IMG2...]]\n"
"\n"
"Options:\n"
"  -h  -?          Show help options\n"
"  -a              Arduino (send tag ids over serial port)\n"
"  -d              Disable graphics\n"
"  -t              Timing of tag extraction\n"
"  -C <bbxhh>      Tag family (default 36h11)\n"
"  -D <id>         Video device ID (if multiple cameras present)\n"
"  -F <fx>         Focal length in pixels\n"
"  -W <width>      Image width (default 640, availability depends on camera)\n"
"  -H <height>     Image height (default 480, availability depends on camera)\n"
"  -S <size>       Tag size (square black frame) in meters\n"
"  -E <exposure>   Manually set camera exposure (default auto; range 0-10000)\n"
"  -G <gain>       Manually set camera gain (default auto; range 0-255)\n"
"  -B <brightness> Manually set the camera brightness (default 128; range 0-255)\n"
"  -X <calibrate>  Calibrate camera (give txt file) \n"
"\n";

const string intro = "\n"
"April Tags Coordinate System Adaptation Example\n"
"Author: by Michael Kaess of MIT\n"
"Adapted by Tristan Schuler & Greta Studier\n"
"(C) 2018 NASA-MSFC\n"
"\n";


// Needed for getopt / command line options processing
#include <unistd.h>
extern int optind;
extern char *optarg;
time_t tstart = time(0);
int start_s = clock();

// For Arduino: locally defined serial port access class
#include "Serial.h"


const char* windowName = "apriltags_demo";


// utility function to provide current system time (used below in
// determining frame rate at which images are being processed)
double tic() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return ((double)t.tv_sec + ((double)t.tv_usec) / 1000000.);
}




#include <cmath>

#ifndef PI
const double PI = 3.14159265358979323846;
#endif
const double TWOPI = 2.0*PI;

/**
* Normalize angle to be within the interval [-pi,pi].
*/
inline double standardRad(double t) {
	if (t >= 0.) {
		t = fmod(t + PI, TWOPI) - PI;
	}
	else {
		t = fmod(t - PI, -TWOPI) + PI;
	}
	return t;
}

/**
* Convert rotation matrix to Euler angles
*/
void wRo_to_euler(const Eigen::Matrix3d& wRo, double& yaw, double& pitch, double& roll) {
	yaw = standardRad(atan2(wRo(1, 0), wRo(0, 0)));
	double c = cos(yaw);
	double s = sin(yaw);
	pitch = standardRad(atan2(-wRo(2, 0), wRo(0, 0)*c + wRo(1, 0)*s));
	roll = standardRad(atan2(wRo(0, 2)*s - wRo(1, 2)*c, -wRo(0, 1)*s + wRo(1, 1)*c));
}


class Demo {

	AprilTags::TagDetector* m_tagDetector;
	AprilTags::TagCodes m_tagCodes;

	bool m_draw; // draw image and April tag detections?
	bool m_arduino; // send tag detections to serial port?
	bool m_timing; // print timing information for each tag extraction call

	int m_width; // image size in pixels
	int m_height;
	double m_tagSize; // April tag side length in meters of square black frame
	double m_fx; // camera focal length in pixels
	double m_fy;
	double m_px; // camera principal point
	double m_py;
	bool calibrate;  //if calibration is needed


	int m_deviceId; // camera id (in case of multiple cameras)

	list<string> m_imgNames;

	cv::VideoCapture m_cap;

	int m_exposure;
	int m_gain;
	int m_brightness;

	Serial m_serial;
	int i;
	FILE *serPort;


public:
	int ctr;
	int innerctr;
	ofstream groupingData;
	ofstream optimizedData;
	double DISTANCE;
	time_t tstart;
	int detectionssize;
	double timenow;
	double timeold = 0;
	double delta_t;
	double xold = 0;
	double yold = 0;
	double xnew;
	double ynew;
	double delta_x;
	double delta_y;
	double velmag;
	double veltheta;
	string write_string;

	double OPTIMIZED_TIME = 0;
	double OPTIMIZED_X = 0;
	double OPTIMIZED_Y = 0;
	double OPTIMIZED_PITCH = 0;
	double OPTIMIZED_ROLL = 0;
	double OPTIMIZED_YAW = 0;
	vector<TagOptimization> Tags;
	Mat cameraMatrix;
	Mat distortionCoefficients;
	

	// default constructor
	Demo() :
		// default settings, most can be modified through command line options (see below)
		m_tagDetector(NULL),
		m_tagCodes(AprilTags::tagCodes36h11),

		m_draw(true),
		m_arduino(false),
		m_timing(false),

		m_width(640),
		m_height(480),
		m_tagSize(0.166),
		m_fx(600),
		m_fy(600),
		m_px(m_width / 2),
		m_py(m_height / 2),

		m_exposure(-1),
		m_gain(-1),
		m_brightness(-1),

		calibrate(false),

		m_deviceId(0)
	{}
	
	//set precision for string output for serial communication with arduino
	template <class T>
	std::string to_string_with_precision(const T a_value, const int n = 3)
		{
		    //std::ostringstream out;
		    //out << std::setprecision(n) << a_value;
		    //return out.str();
		stringstream stream;
		stream << fixed << setprecision(n) << a_value;
		return stream.str();
		} 

	void openCSV(string TOD, string header, string optimizedheader) {
		groupingData.open("Data/" + TOD + "_AllTags.csv");
		optimizedData.open("Data/" + TOD + "_OptimizedData.csv");
		groupingData << header;
		optimizedData << optimizedheader;
		innerctr = 0;
		ctr = 0;
		detectionssize = 0;
	}

	//Takes in name of calibration text file as single argument
	bool loadCameraCalibration(string name) {
		ifstream inStream(name.c_str());
		if (inStream)
		{

			uint16_t rows;
			uint16_t columns;

			inStream >> rows;
			inStream >> columns;

			cameraMatrix = Mat(Size(rows, columns), CV_64F);

			for (int r = 0; r < rows; r++)
			{
				for (int c = 0; c < columns; c++)
				{
					double read = 0.0f;
					inStream >> read;
					cameraMatrix.at<double>(r, c) = read;
					//cout << cameraMatrix.at<double>(r, c) << endl;

				}
			}

			//Distance Coeeficients

			inStream >> rows;
			inStream >> columns;

			distortionCoefficients = Mat::zeros(rows, columns, CV_64F);
			for (int r = 0; r < rows; r++)
			{
				for (int c = 0; c < columns; c++)
				{
					double read = 0.0f;
					inStream >> read;
					distortionCoefficients.at<double>(r, c) = read;
					//cout << distortionCoefficients.at<double>(r, c) << endl;

				}
			}

			inStream.close();
			cout << "Camera Calibrated!" << endl;
			//cout << "Camera Matrix: " << cameraMatrix << endl;
			//cout << "Distortion Coefficients: " << distortionCoefficients << endl;
			return true;

		}

		cout << name << " not found." << endl;
		return false;
	}




	// changing the tag family
	void setTagCodes(string s) {
		if (s == "16h5") {
			m_tagCodes = AprilTags::tagCodes16h5;
		}
		else if (s == "25h7") {
			m_tagCodes = AprilTags::tagCodes25h7;
		}
		else if (s == "25h9") {
			m_tagCodes = AprilTags::tagCodes25h9;
		}
		else if (s == "36h9") {
			m_tagCodes = AprilTags::tagCodes36h9;
		}
		else if (s == "36h11") {
			m_tagCodes = AprilTags::tagCodes36h11;
		}
		else {
			cout << "Invalid tag family specified" << endl;
			exit(1);
		}
	}

	// parse command line options to change default behavior
	void parseOptions(int argc, char* argv[]) {
		int c;
		while ((c = getopt(argc, argv, ":h?adtC:X:F:H:S:W:E:G:B:D:")) != -1) {
			// Each option character has to be in the string in getopt();
			// the first colon changes the error character from '?' to ':';
			// a colon after an option means that there is an extra
			// parameter to this option; 'W' is a reserved character
			switch (c) {
			case 'h':
			case '?':
				cout << intro;
				cout << usage;
				exit(0);
				break;
			case 'a':
				m_arduino = true;
				break;
			case 'd':
				m_draw = false;
				break;
			case 't':
				m_timing = true;
				break;
			case 'C':
				setTagCodes(optarg);
				break;
			case 'X':
				calibrate = loadCameraCalibration(optarg);
				break;
			case 'F':
				m_fx = atof(optarg);
				m_fy = m_fx;
				break;
			case 'H':
				m_height = atoi(optarg);
				m_py = m_height / 2;
				break;
			case 'S':
				m_tagSize = atof(optarg);
				break;
			case 'W':
				m_width = atoi(optarg);
				m_px = m_width / 2;
				break;
			case 'E':
#ifndef EXPOSURE_CONTROL
				cout << "Error: Exposure option (-E) not available" << endl;
				exit(1);
#endif
				m_exposure = atoi(optarg);
				break;
			case 'G':
#ifndef EXPOSURE_CONTROL
				cout << "Error: Gain option (-G) not available" << endl;
				exit(1);
#endif
				m_gain = atoi(optarg);
				break;
			case 'B':
#ifndef EXPOSURE_CONTROL
				cout << "Error: Brightness option (-B) not available" << endl;
				exit(1);
#endif
				m_brightness = atoi(optarg);
				break;
			case 'D':
				m_deviceId = atoi(optarg);
				break;
			case ':': // unknown option, from getopt
				cout << intro;
				cout << usage;
				exit(1);
				break;
			}
		}

		if (argc > optind) {
			for (int i = 0; i < argc - optind; i++) {
				m_imgNames.push_back(argv[optind + i]);
			}
		}
	}

	void setup() {
		m_tagDetector = new AprilTags::TagDetector(m_tagCodes);

		// prepare window for drawing the camera images
		if (m_draw) {
			cv::namedWindow(windowName, 1);
		}

		// optional: prepare serial port for communication with Arduino
		if (m_arduino) {S
			//m_serial.open("/dev/ttyACM0", 57600);
			m_serial.open("/dev/ttyUSB0", 57600);
		}
	}

	void setupVideo() {

#ifdef EXPOSURE_CONTROL
		// manually setting camera exposure settings; OpenCV/v4l1 doesn't
		// support exposure control; so here we manually use v4l2 before
		// opening the device via OpenCV; confirmed to work with Logitech
		// C270; try exposure=20, gain=100, brightness=150

		string video_str = "/dev/video0";
		video_str[10] = '0' + m_deviceId;
		int device = v4l2_open(video_str.c_str(), O_RDWR | O_NONBLOCK);

		if (m_exposure >= 0) {
			// not sure why, but v4l2_set_control() does not work for
			// V4L2_CID_EXPOSURE_AUTO...
			struct v4l2_control c;
			c.id = V4L2_CID_EXPOSURE_AUTO;
			c.value = 1; // 1=manual, 3=auto; V4L2_EXPOSURE_AUTO fails...
			if (v4l2_ioctl(device, VIDIOC_S_CTRL, &c) != 0) {
				cout << "Failed to set... " << strerror(errno) << endl;
			}
			cout << "exposure: " << m_exposure << endl;
			v4l2_set_control(device, V4L2_CID_EXPOSURE_ABSOLUTE, m_exposure * 6);
		}
		if (m_gain >= 0) {
			cout << "gain: " << m_gain << endl;
			v4l2_set_control(device, V4L2_CID_GAIN, m_gain * 256);
		}
		if (m_brightness >= 0) {
			cout << "brightness: " << m_brightness << endl;
			v4l2_set_control(device, V4L2_CID_BRIGHTNESS, m_brightness * 256);
		}
		v4l2_close(device);
#endif 

		// find and open a USB camera (built in laptop camera, web cam etc)
		m_cap = cv::VideoCapture(m_deviceId);
		if (!m_cap.isOpened()) {
			cerr << "ERROR: Can't find video device " << m_deviceId << "\n";
			exit(1);
		}
		m_cap.set(CV_CAP_PROP_FRAME_WIDTH, m_width);
		m_cap.set(CV_CAP_PROP_FRAME_HEIGHT, m_height);
		cout << "Camera successfully opened (ignore error messages above...)" << endl;
		cout << "Actual resolution: "
			<< m_cap.get(CV_CAP_PROP_FRAME_WIDTH) << "x"
			<< m_cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;

	}

	void print_detection(AprilTags::TagDetection& detection) {
		cout << "  Id: " << detection.id
			<< " (Hamming: " << detection.hammingDistance << ")";

		// recovering the relative pose of a tag:

		// NOTE: for this to be accurate, it is necessary to use the
		// actual camera parameters here as well as the actual tag size
		// (m_fx, m_fy, m_px, m_py, m_tagSize)

		Eigen::Vector3d translation;
		Eigen::Matrix3d rotation;
		detection.getRelativeTranslationRotation(m_tagSize, m_fx, m_fy, m_px, m_py,
			translation, rotation);

		Eigen::Matrix3d F;
		F <<
			1, 0, 0,
			0, -1, 0,
			0, 0, 1;
		Eigen::Matrix3d fixed_rot = F*rotation;
		double yaw, pitch, roll;
		wRo_to_euler(fixed_rot, yaw, pitch, roll);

		DISTANCE = translation.norm();

		cout << "  distance=" << translation.norm()
			<< "m, x=" << translation(1)*1
			<< ", y=" << translation(2)
			<< ", z=" << translation(0)
			<< ", yaw=" << yaw
			<< ", pitch=" << pitch
			<< ", roll=" << roll
			<< endl;

		//test << detection.id << "," << DISTANCE
		groupingData << std::fixed << std::setprecision(3) <<
			ctr << "," <<
			(clock() - start_s) / (double(CLOCKS_PER_SEC)) << ","
			<< detection.id << ","
			<< translation.norm() << ","
			<< translation(1)*1 << ","
			<< translation(2) << ","
			<< translation(0) << ","
			<< pitch << ","
			<< roll << ","
			<< yaw << ","
			<< endl;

		//TagOptimization(TIME, TAGID, X, Y, PITCH, ROLL, YAW)
		TagOptimization t((clock() - start_s) / (double(CLOCKS_PER_SEC)), detection.id, translation(1)*1,
			translation(2), pitch, roll, yaw);
		Tags.push_back(t);

		innerctr++;
		if (innerctr == detectionssize) {
			innerctr = 0;
			ctr++;
		}



		// Also note that for SLAM/multi-view application it is better to
		// use reprojection error of corner points, because the noise in
		// this relative pose is very non-Gaussian; see iSAM source code
		// for suitable factors.
	}

	void processImage(cv::Mat& image, cv::Mat& image_gray) {

		//test << getDISTANCE() << "test" << endl;
		// alternative way is to grab, then retrieve; allows for
		// multiple grab when processing below frame rate - v4l keeps a
		// number of frames buffered, which can lead to significant lag
		//      m_cap.grab();
		//      m_cap.retrieve(image);

		// detect April tags (requires a gray scale image)
		cv::cvtColor(image, image_gray, CV_BGR2GRAY);
		double t0;
		if (m_timing) {
			t0 = tic();
		}
		vector<AprilTags::TagDetection> detections = m_tagDetector->extractTags(image_gray);
		if (m_timing) {
			double dt = tic() - t0;
			cout << "Extracting tags took " << dt << " seconds." << endl;
		}

		// print out each detection
		detectionssize = detections.size();
		cout << detections.size() << " tags detected:" << endl;
		for (int i = 0; i < detections.size(); i++) {
			print_detection(detections[i]);
		}

		OPTIMIZED_X = 0;
		OPTIMIZED_Y = 0;
		OPTIMIZED_PITCH = 0;
		OPTIMIZED_ROLL = 0;
		OPTIMIZED_YAW = 0;

		//Iterate over list of Tags to determine real position
		for (int i = 0; i < Tags.size(); i++) {
			OPTIMIZED_X += Tags[i].CAMERA_X;
			OPTIMIZED_Y += Tags[i].CAMERA_Y;
			OPTIMIZED_PITCH += Tags[i].pitch;
			OPTIMIZED_ROLL += Tags[i].roll;
			OPTIMIZED_YAW += Tags[i].yaw;
		}


		if (OPTIMIZED_X != NULL) {
			OPTIMIZED_X = (OPTIMIZED_X / Tags.size());
			OPTIMIZED_Y = OPTIMIZED_Y / Tags.size();
			OPTIMIZED_PITCH = OPTIMIZED_PITCH / Tags.size();
			OPTIMIZED_ROLL = OPTIMIZED_ROLL / Tags.size();
			OPTIMIZED_YAW = OPTIMIZED_YAW / Tags.size();
		
		xnew = OPTIMIZED_X;
		ynew = OPTIMIZED_Y;
		timenow = (clock() - start_s) / (double(CLOCKS_PER_SEC));

		delta_t = timenow - timeold;
		timeold = timenow;
		delta_x = xnew -xold;
		delta_y = ynew -yold;	
		xold = xnew;
		yold = ynew;
		velmag = sqrt(pow(delta_x/delta_t,2) + pow(delta_y/delta_t,2));
		veltheta =  atan(delta_y/delta_x);
		veltheta = veltheta * 180 / M_PI;		
		
//Coordinate System:     0°
//                       |     
//                 90°---|---270°
//                       |  
//                      180°

		if(delta_x >=0 && delta_y >= 0){ 
			veltheta = 360-veltheta;
		}
		if(delta_x <=0 && delta_y >= 0){ 
			veltheta = 90 - fabs(veltheta);
		}
		if(delta_x <=0 && delta_y <= 0){ 
			veltheta =180 - fabs(veltheta);
		}
		if(delta_x >=0 && delta_y <= 0){ 
			veltheta = 270-fabs(veltheta);
		}


			cout << "OPTIMIZED X: " << OPTIMIZED_X << " OPTIMIZED_Y: " << OPTIMIZED_Y << " OPTIMIZED_PITCH: " << OPTIMIZED_PITCH
				<< " OPTIMIZED_ROLL: " << OPTIMIZED_ROLL << " OPTIMIZED_YAW: " << OPTIMIZED_YAW << " Velocity_X: "<< delta_x/delta_t 
				<< " Velocity_Y: " << delta_y/delta_t << " Velocity_Mag: " << velmag << " Velocity_theta: " << veltheta << endl;

		optimizedData << std::fixed << std::setprecision(3) <<
			(clock() - start_s) / (double(CLOCKS_PER_SEC)) << ","
			<< OPTIMIZED_X << ","
			<< OPTIMIZED_Y << ","
			<< OPTIMIZED_PITCH << ","
			<< OPTIMIZED_ROLL << ","
			<< OPTIMIZED_YAW << ","
			<< delta_x/delta_t << ","
			<< delta_y/delta_t << ","
			<< velmag << ","
			<< veltheta << ","
			<< endl;
		
		//string for serial communication between pi and arduino
		write_string = to_string_with_precision(OPTIMIZED_X) + "," + to_string_with_precision(OPTIMIZED_Y) + "," + to_string_with_precision(OPTIMIZED_PITCH) + "," + 
			to_string_with_precision(OPTIMIZED_ROLL) + "," + to_string_with_precision(OPTIMIZED_YAW) + "," + to_string_with_precision(delta_x/delta_t) + "," + 
			to_string_with_precision(delta_y/delta_t) + "," + to_string_with_precision(velmag) + "," + to_string_with_precision(veltheta);

		}


		cout << "\nTAG SIZE" << Tags.size() << "\n";
		Tags.clear();



		time_t t;
		struct tm tm;
		struct tm * tmp;

		t = mktime(&tm);
		//tmp = localtime(t);

		//std::cout << std::setprecision(2)

		std::cout << std::fixed << "Real Time: " << std::setprecision(3) << (clock() - start_s) / (double(CLOCKS_PER_SEC)) << std::endl;

		// show the current image including any detections
		if (m_draw) {
			for (int i = 0; i < detections.size(); i++) {
				// also highlight in the image
				detections[i].draw(image);
			}

			line(image, Point((image.cols / 2) - 50, image.rows / 2), Point((image.cols / 2) + 50, image.rows / 2), Scalar(0, 0, 255), 1);
			line(image, Point(image.cols / 2, (image.rows / 2) - 50), Point(image.cols / 2, (image.rows / 2) + 50), Scalar(0, 0, 255), 1);

			imshow(windowName, image); // OpenCV call

		}

		// optionally send tag information to serial port (e.g. to Arduino)
		if (m_arduino) {
			if (detections.size() > 0) {
				// only the first detected tag is sent out for now
				Eigen::Vector3d translation;
				Eigen::Matrix3d rotation;
				detections[0].getRelativeTranslationRotation(m_tagSize, m_fx, m_fy, m_px, m_py,
					translation, rotation);
				/*
				m_serial.print(detections[0].id);
				m_serial.print(",");
				m_serial.print(translation(0));
				m_serial.print(",");
				m_serial.print(translation(1));
				m_serial.print(",");
				m_serial.print(translation(2));
				m_serial.print("\n");
				*/
				m_serial.print(write_string);
				m_serial.print("\n");
				
			}
			else {
				// no tag detected: tag ID = -1
				m_serial.print("-1,0.0,0.0,0.0\n");
			}
		}
	}

	// Load and process a single image
	void loadImages() {
		cv::Mat image;
		cv::Mat image_gray;

		for (list<string>::iterator it = m_imgNames.begin(); it != m_imgNames.end(); it++) {
			image = cv::imread(*it); // load image with opencv
			processImage(image, image_gray);
			while (cvWaitKey(100) == -1) {}
		}
	}

	// Video or image processing?
	bool isVideo() {
		return m_imgNames.empty();
	}

	// The processing loop where images are retrieved, tags detected,
	// and information about detections generated
	void loop() {

		cv::Mat image;
		cv::Mat image_gray;
		cv::Mat imageUndistorted;


		int frame = 0;
		double last_t = tic();
		while (true) {

			// capture frame
			m_cap >> image;


			if (calibrate) {
				undistort(image, imageUndistorted, cameraMatrix, distortionCoefficients);
				processImage(imageUndistorted, image_gray);
				//flip(image,image,1);
			}
			else
				processImage(image, image_gray);

			// print out the frame rate at which image frames are being processed
			frame++;
			if (frame % 10 == 0) {
				double t = tic();
				cout << "  " << 10. / (t - last_t) << " fps" << endl;
				last_t = t;
			}

			// exit if any key is pressed
			if (cvWaitKey(10) >= 0) break;
		}
	}

}; // Demo


   // here is were everything begins
int main(int argc, char* argv[]) {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	Demo demo;


	// process command line options
	demo.parseOptions(argc, argv);


	demo.setup();


	//string filename = to_string(tm.tm_year + 1900);
	string TOD = to_string(tm.tm_mon + 1) + "-"
		+ to_string(tm.tm_mday) + "-" + to_string(tm.tm_year + 1900) + "-" + to_string(tm.tm_hour)
		+ ":" + to_string(tm.tm_min) + ":" + to_string(tm.tm_sec);

	cout << "Current TOD: " << TOD << endl;

	string header = "Count,Time,Tag ID,Distance,X,Y,Z,Pitch,Roll,Yaw\n";
	string optimizedheader = "Time,X,Y,Pitch,Roll,Yaw,Velx,Vely,Velmag,Veltheta\n";
	demo.openCSV(TOD, header, optimizedheader);
	//ofstream a("test.csv");
	//a << header;


	if (demo.isVideo()) {
		cout << "Processing video" << endl;

		// setup image source, window for drawing, serial port...
		demo.setupVideo();

		// the actual processing loop where tags are detected and visualized
		demo.loop();

	}
	else {
		cout << "Processing image" << endl;

		// process single image
		demo.loadImages();

	}

	//a.close();
	demo.groupingData.close();

	return 0;
}

