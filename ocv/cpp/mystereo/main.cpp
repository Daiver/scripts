#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <vector>
#include <queue>

class Point
{
public:
    int X, Y;
    Point(int X, int Y) {this->X = X; this->Y = Y;}
};

class Expander
{
public:
    std::vector<int> steps;
    int rows, cols;
    Expander(int row, int cols)
    {
        this->rows = rows;
        this->cols = cols;
        steps.push_back(0);
    }
};

void someWork(cv::Mat const &depth_map)
{
    //uint8_t* pixelPtr = (uint8_t*)depth_map.data;
    //std::cout << depth_map;
    std::cout << (short)depth_map.data[0]; //[(depth_map.rows) * (depth_map.cols) - 1];
}

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
    someWork(map);
    cv::Mat adjMap = normalize(map);
    cv::imshow("Out", adjMap);

    cv::imshow("left", left);
    cv::imshow("right", right);
    while (cv::waitKey() % 0x100 != 27){};
    return 0;
}
