#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/contrib/contrib.hpp>

#include <iostream>
#include <vector>
//using namespace cv;

float *getHOG(const cv::Mat &image, int* count)
{
    cv::HOGDescriptor hog;
    std::vector<float> res;
    std::cout<<"Before compute\n";
    hog.compute(image, res, cv::Size(8,8), cv::Size(0,0));
    std::cout<<"Before size\n";
    *count = res.size();
    return &res[0];
}

float **getTraininigData(int* setlen, int* veclen)
{
    char *names[2] = {
        "../faces/s1/1.pgm",
        "../faces/s1/2.pgm",
    };
    for(int i = 0; i < 2; i++)
    {
        std::cout<<names[i]<<"\n";
        cv::Mat img = cv::imread(names[i], 0);
        getHOG(img, veclen);
        std::cout<<"vl "<<*veclen<<"\n";
    }
}

int main()
{
    int setlen, veclen;
    getTraininigData(&setlen, &veclen);
    // Data for visual representation
    int width = 512, height = 512;
    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);

    // Set up training data
    float labels[4] = {1.0, -1.0, -1.0, -1.0};
    cv::Mat labelsMat(4, 1, CV_32FC1, labels);

    float trainingData[4][2] = { {501, 10}, {255, 10}, {501, 255}, {10, 501} };

    cv::Mat trainingDataMat(4, 2, CV_32FC1, trainingData);
    //std::cout << trainingDataMat.at<float>(2, 1) << "\n"; //255

    // Set up SVM's parameters
    cv::SVMParams params;
    params.svm_type    = cv::SVM::C_SVC;
    params.kernel_type = cv::SVM::LINEAR;
    params.term_crit   = cv::TermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);

    // Train the SVM
    cv::SVM SVM;
    SVM.train(trainingDataMat, labelsMat, cv::Mat(), cv::Mat(), params);

    cv::Vec3b green(0,255,0), blue (255,0,0);
    // Show the decision regions given by the SVM
    for (int i = 0; i < image.rows; ++i)
        for (int j = 0; j < image.cols; ++j)
        {
            cv::Mat sampleMat = (cv::Mat_<float>(1,2) << i,j);
            float response = SVM.predict(sampleMat);

            if (response == 1)
                image.at<cv::Vec3b>(j, i)  = green;
            else if (response == -1)
                 image.at<cv::Vec3b>(j, i)  = blue;
        }

    // Show the training data
    int thickness = -1;
    int lineType = 8;
    cv::circle( image, cv::Point(501,  10), 5, cv::Scalar(  0,   0,   0), thickness, lineType);
    cv::circle( image, cv::Point(255,  10), 5, cv::Scalar(255, 255, 255), thickness, lineType);
    cv::circle( image, cv::Point(501, 255), 5, cv::Scalar(255, 255, 255), thickness, lineType);
    cv::circle( image, cv::Point( 10, 501), 5, cv::Scalar(255, 255, 255), thickness, lineType);

    // Show support vectors
    thickness = 2;
    lineType  = 8;
    int c     = SVM.get_support_vector_count();

    for (int i = 0; i < c; ++i)
    {
        const float* v = SVM.get_support_vector(i);
        cv::circle( image,  cv::Point( (int) v[0], (int) v[1]),   6,  cv::Scalar(128, 128, 128), thickness, lineType);
    }

    cv::imwrite("result.png", image);        // save the image

    cv::imshow("SVM Simple Example", image); // show it to the user
    cv::waitKey(0);

}
