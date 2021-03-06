#include <stdio.h>
#include <math.h>

#include "lktracker.h"

void LKTracker::initPoints(cv::Mat& gray, std::vector<cv::Point2f>& points, const int MAX_COUNT)
{
    goodFeaturesToTrack(gray, points, MAX_COUNT, 0.01, 10, cv::Mat(), 3, 0, 0.04);
    cornerSubPix(gray, points, *this->subPixWinSize, cv::Size(-1,-1), *this->termcrit);
}

LKTracker::LKTracker()
{
    this->termcrit = new cv::TermCriteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS,20,0.03);
    this->subPixWinSize = new cv::Size(10, 10);
    this->winSize = new cv::Size(31, 31);
}

void LKTracker::init(cv::Mat& gray)
{
    this->initPoints(gray, this->points[1], this->MAX_COUNT);
    this->initPoints(gray, this->points[0], this->MAX_COUNT);
    gray.copyTo(this->old_gray);
}

float dist(cv::Point2f& a, cv::Point2f& b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

std::vector<cv::Point2f> LKTracker::track(cv::Mat& gray, bool* is_good)
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
            printf("%d %f\n", i, dist(points[1][i], points[0][i]));
            points[1][k++] = points[1][i];
        }
        points[1].resize(k);
    }
    std::swap(this->points[1], this->points[0]);
    cv::swap(this->old_gray, gray);
    return this->points[0];
}

