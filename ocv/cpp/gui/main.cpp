#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <vector>
#include <queue>
#include <fstream>
#include <stdio.h>

void on_trackbar( int, void* )
{
    
}

int main(int argc, char** argv)
{
    cv::Mat img = cv::Mat::zeros(100, 200, CV_8S);
    cv::imshow("", img);
    int alpha_slider = 9;
    cv::createTrackbar( "tracky", "", &alpha_slider, 10, on_trackbar );
    cv::waitKey();
    return 0;
}
