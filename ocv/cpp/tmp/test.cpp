#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
int main() {
    char var;
    cv::Mat img;
    cv::StereoBM(0);
    img = cv::imread("../tmp2/Image0.jpg");
    cv::namedWindow("Image");
    cv::imshow("Image", img);
    cv::waitKey();
    return 0;
}
