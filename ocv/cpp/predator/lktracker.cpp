#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <opencv/cv.h>

#include <iostream>
#include <vector>

cv::Mat toGray(const cv::Mat& rgb_image)
{
    cv::Mat res;
    cv::cvtColor(rgb_image, res, CV_RGB2GRAY);
    return res;
}


int main(int argc, char** argv)
{
    cv::VideoCapture mptr(0);
    // Obtain first image and set up two feature vectors
    cv::Mat image_prev, image_next;
    std::vector<cv::Point> features_prev, features_next;

    mptr >> image_next;
    mptr >> image_next;
    cv::waitKey(10);
    mptr >> image_next;
    mptr >> image_next;
    cv::waitKey(10);
    mptr >> image_next;
    mptr >> image_next;
    cv::waitKey(10);
    image_next = toGray(image_next);
    cv::imshow("", image_next);
    cv::waitKey(100);
    // Obtain initial set of features
    cv::goodFeaturesToTrack(image_next, // the image 
      features_next,   // the output detected features
      500,//max_count,  // the maximum number of features 
      0.3, //qlevel,     // quality level
      7//minDist     // min distance between two features
    );
    std::cout<<"points "<<features_next.size();

    // Tracker is initialised and initial features are stored in features_next
    // Now iterate through rest of images
    for(;;)
    {
        image_prev = image_next.clone();
        features_prev = features_next;
        mptr >> image_next;// = getImage();  // Get next image
        image_next = toGray(image_next);
        std::vector<bool> status ;
        std::vector<float> err ;
        // Find position of feature in new image
        cv::calcOpticalFlowPyrLK(
          image_prev, image_next, // 2 consecutive images
          features_prev,//points_prev, // input point positions in first im
          features_next, // output point positions in the 2nd
          status,    // tracking success
          err      // tracking error
        );

        cv::imshow("image", image_next);
        cv::waitKey(1);
    }
}
