//
//  main.cpp
//  TestCalibration
//
//  Created by Greta Studier on 2/20/18.
//  Copyright © 2018 Greta Studier. All rights reserved.
//
/*
 Gucci for black camera on pi:
 [712.3569356101527, 0, 320.3506904372541;
 0, 664.8499666468488, 248.0466493007159;
 0, 0, 1]
 [-0.3650007185118307, -0.08256361261458915, -0.002138937839550542, -0.006064527080443616, 0.5223015320119493]

 My Webcam:
 [0.9858043200721776, 58.37314737496447, 0.000890380937589476, -0.01440380191495337, 0.3703751612149476][4033.815885202904, 0, 634.1807171926924;
 0, 3105.07351107567, 347.0902196076579;
 0, 0, 1]
 */
#include <sstream>
#include <stdio.h>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/video/tracking.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

int main() {
    
    Mat intrinsic = Mat(3, 3, CV_32FC1);
    
    //my camera
      intrinsic.ptr<float>(0)[0] = 4033.815885202904;
      intrinsic.ptr<float>(0)[1] = 0;
      intrinsic.ptr<float>(0)[2] = 634.1807171926924;
      intrinsic.ptr<float>(1)[0] = 0;
      intrinsic.ptr<float>(1)[1] = 3105.07351107567;
      intrinsic.ptr<float>(1)[2] = 248.0466493007159;
      intrinsic.ptr<float>(2)[0] = 0;
      intrinsic.ptr<float>(2)[1] = 0;
      intrinsic.ptr<float>(2)[2] = 1;
    
    //Black camera on pi:
//    intrinsic.ptr<float>(0)[0] = 712.3569356101527;
//    intrinsic.ptr<float>(0)[1] = 0;
//    intrinsic.ptr<float>(0)[2] = 320.3506904372541;
//    intrinsic.ptr<float>(1)[0] = 0;
//    intrinsic.ptr<float>(1)[1] = 664.8499666468488;
//    intrinsic.ptr<float>(1)[2] = 347.0902196076579;
//    intrinsic.ptr<float>(2)[0] = 0;
//    intrinsic.ptr<float>(2)[1] = 0;
//    intrinsic.ptr<float>(2)[2] = 1;
    
    Mat distCoeffs = Mat(1, 5, CV_32FC1);
    
    //My camera:
    distCoeffs.ptr<float>(0)[0] = 0.9858043200721776;
    distCoeffs.ptr<float>(0)[1] = 58.37314737496447;
    distCoeffs.ptr<float>(0)[2] = 0.000890380937589476;
    distCoeffs.ptr<float>(0)[3] = -0.01440380191495337;
    distCoeffs.ptr<float>(0)[4] =  0.3703751612149476;
    
    //Black camera on pi:
//    distCoeffs.ptr<float>(0)[0] = -0.3650007185118307;
//    distCoeffs.ptr<float>(0)[1] = -0.08256361261458915;
//    distCoeffs.ptr<float>(0)[2] = -0.002138937839550542;
//    distCoeffs.ptr<float>(0)[3] = -0.006064527080443616;
//    distCoeffs.ptr<float>(0)[4] =  0.5223015320119493;
    
    cout << "Intrinsic:"<< intrinsic<< endl;
    cout << "distCoeffs:"<< distCoeffs<< endl;
    
    //open webcam
    VideoCapture capture = VideoCapture(0);
    
    Mat image;
    Mat imageUndistorted;
    
    while(1)
    {
        capture >> image;
        
        //create centerpoint
        line(image, Point(image.cols/2, (image.rows/2)-60), Point(image.cols/2, (image.rows/2)+60), Scalar(10,0,220), 1);  //crosshair vertical
        line(image, Point((image.cols/2)-60, (image.rows/2)), Point((image.cols/2)+60, (image.rows/2)), Scalar(10,0,220),1);  //crosshair horizontal
        
        undistort(image, imageUndistorted, intrinsic, distCoeffs);
        
        //resize windows
        resize(image, image, Size(700,500));
        imshow("win1", image);
        resizeWindow("wind1", 700, 500);
        resize(imageUndistorted, imageUndistorted, Size(700,500));
        imshow("win2", imageUndistorted);
        resizeWindow("wind2", 700, 500);
        waitKey(1);
    }
}
