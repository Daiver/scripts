#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
int main() {
    char var;
    cv::StereoBM bm(CV_STEREO_BM_NORMALIZED_RESPONSE);
    //cv::Mat img;
    //img = cv::imread("../tmp2/Image0.jpg");
    cv::Mat left  = cv::imread("tsukuba/scene1.row3.col3.ppm");
    cv::Mat right = cv::imread("tsukuba/scene1.row3.col5.ppm");
    cv::Mat res; 
    bm(left, right, res);

    cv::namedWindow("left");
    cv::imshow("left", left);
    cv::namedWindow("right");
    cv::imshow("right", right);
    cv::waitKey();
    return 0;
}
