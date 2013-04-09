#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

cv::Mat getDepthMap(cv::Mat const &left, cv::Mat const &right)
{
    cv::Mat res; 
    cv::StereoBM bm(CV_STEREO_BM_NORMALIZED_RESPONSE);
    bm(left, right, res);
    return res;
}

cv::Mat normalize(cv::Mat const &depth_map)
{
    double min;
    double max;
    cv::minMaxIdx(depth_map, &min, &max);
    cv::Mat adjMap;
    cv::convertScaleAbs(depth_map, adjMap, 255 / max);
    return adjMap;
}

int main(int argc, char **argv) {
    //cv::Mat img;
    //img = cv::imread("../tmp2/Image0.jpg");
    auto left_name  = "tsukuba/scene1.row3.col3.ppm";
    auto right_name = "tsukuba/scene1.row3.col5.ppm";
    if (argc > 2)
    {
        left_name = argv[1];
        right_name = argv[2];
    }
    cv::Mat left  = cv::imread(left_name, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat right = cv::imread(right_name, CV_LOAD_IMAGE_GRAYSCALE);
    //res[0][0] = 100;
    cv::Mat map = getDepthMap(left, right);
    cv::Mat adjMap = normalize(map);
    cv::imshow("Out", adjMap);

    cv::imshow("left", left);
    cv::imshow("right", right);
    cv::waitKey();
    return 0;
}
