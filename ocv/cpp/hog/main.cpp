#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <vector>
#include <queue>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "peopledetect.h"

int main(int argc, char** argv)
{
    cv::Mat img;
    cv::HOGDescriptor hog;
    hog.setSVMDetector(getThisPeopleDetector());
    img = cv::imread(argv[1]);
    std::vector<cv::Rect> found, found_filtered;
    hog.detectMultiScale(img, found, 4, cv::Size(8,8), cv::Size(32,32), 1.05, 23);
    for(auto r : found)
    {
        std::cout<<r<<"\n";
        cv::rectangle(img, r, cv::Scalar(255, 0, 0));
    }
    cv::imshow("", img);
    cv::waitKey();
    return 0;
}
