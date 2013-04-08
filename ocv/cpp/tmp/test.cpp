#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
int main() {
    char var;
    cv::Mat img;
    img = cv::imread("C:/test/img.jpg");
    cv::namedWindow("Image");
    cv::imshow("Image", img);
    std::cin >> var;
    return 0;
}
