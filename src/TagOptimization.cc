#include <iostream>
#include "TagOptimization.h"
#include <cmath>

namespace AprilTags{
	void TagOptimization::set(double TIME, int TAGID, double x, double y, double PITCH, double ROLL, double YAW){
	time = TIME; tagID = TAGID; X = x; Y = y; pitch = PITCH; roll = ROLL; yaw = YAW;
	}
	void TagOptimization::optimize(){
		//Determine QR's coordinates given ID
		QR_X = coordinates[tagID][0];
		QR_Y = coordinates[tagID][1];
		//Determine Camera Position in relation to QR Coordinate
		//convert radians to degrees
		pitch = pitch * 180 / M_PI;
		roll = roll * 180 / M_PI;
		yaw = yaw * 180 / M_PI;
		//Coordinate System has to be rotated to account for orientation of camera
		QR_X_Rot = QR_X*cos(yaw) - QR_Y*sin(yaw);
		QR_Y_Rot = QR_Y*cos(yaw) + QR_X*sin(yaw);
		CAMERA_X = QR_X_Rot - X;
		CAMERA_Y = QR_Y_Rot - Y;
	}


	void TagOptimization::print() {
	std::cout << "Camera X: " << CAMERA_X << " Camera Y: " << CAMERA_Y << std::endl;
	}
}
