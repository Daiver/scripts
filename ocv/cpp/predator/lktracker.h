#ifndef __LKTRACKER_H__
#define __LKTRACKER_H__

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class Tracker
{
public:
    Tracker()
    {
        this->termcrit = new cv::TermCriteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS,20,0.03);
        this->subPixWinSize = new cv::Size(10, 10);
        this->winSize = new cv::Size(31, 31);
    }

    void init(cv::Mat& gray)
    {
        this->initPoints(gray, this->points[1], this->MAX_COUNT);
        this->initPoints(gray, this->points[0], this->MAX_COUNT);
        gray.copyTo(this->old_gray);
    }

    std::vector<cv::Point2f> track(cv::Mat& gray, bool* is_good)
    {
        this->initPoints(gray, this->points[1], this->MAX_COUNT);
        *is_good = !this->points[0].empty();
        if(*is_good)
        {
            std::vector<uchar> status;
            std::vector<float> err;
            if(this->old_gray.empty())
                gray.copyTo(this->old_gray);
            cv::calcOpticalFlowPyrLK(this->old_gray, gray, this->points[0], this->points[1], status, err, *this->winSize,
                                 3, *this->termcrit, 0, 0.001);
            size_t i, k;
            for( i = k = 0; i < points[1].size(); i++ )
            {
                if( !status[i] )
                    continue;

                points[1][k++] = points[1][i];
                //circle( image, points[1][i], 3, Scalar(0,255,0), -1, 8);
            }
            points[1].resize(k);
        }
        std::swap(this->points[1], this->points[0]);
        cv::swap(this->old_gray, gray);
        return this->points[0];
    }

private:
    void initPoints(cv::Mat& gray, std::vector<cv::Point2f>& points, const int MAX_COUNT)
    {
        goodFeaturesToTrack(gray, points, MAX_COUNT, 0.01, 10, cv::Mat(), 3, 0, 0.04);
        cornerSubPix(gray, points, *this->subPixWinSize, cv::Size(-1,-1), *this->termcrit);
    }

    const int MAX_COUNT = 500;
    std::vector<cv::Point2f> points[2];
    cv::Mat old_gray;
    cv::TermCriteria *termcrit;
    cv::Size *winSize, *subPixWinSize;
};



#endif

