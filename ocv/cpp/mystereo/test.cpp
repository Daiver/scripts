#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
int main(int argc, char **argv) {
    char var;
    cv::StereoBM bm(CV_STEREO_BM_NORMALIZED_RESPONSE);
    //cv::Mat img;
    //img = cv::imread("../tmp2/Image0.jpg");
    auto left_name  = "tsukuba/scene1.row3.col3.ppm";
    auto right_name = "tsukuba/scene1.row3.col5.ppm";
    cv::Mat left  = cv::imread(left_name, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat right = cv::imread(right_name, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat res; 
    bm(left, right, res);
    //res[0][0] = 100;
    double min;
    double max;
    cv::minMaxIdx(res, &min, &max);
    cv::Mat adjMap;
    cv::convertScaleAbs(res, adjMap, 255 / max);
    cv::imshow("Out", adjMap);

    cv::imshow("left", left);
    cv::imshow("right", right);
    cv::waitKey();
    return 0;
}
