#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include "opencv2/contrib/contrib.hpp"
#include <vector>
#include <queue>

//#define AT_TYPE short
#define AT_TYPE char

class Point
{
public:
    int X, Y;
    Point(int X, int Y) {this->X = X; this->Y = Y;}
};

class Component
{
public:
    std::vector<Point> points;
    int X1, X2, Y1, Y2, width, height;
    double std, mean;
};

cv::Mat normalize(cv::Mat const &depth_map)
{
    double min;
    double max;
    cv::minMaxIdx(depth_map, &min, &max);
    cv::Mat adjMap;
    cv::convertScaleAbs(depth_map, adjMap, 255 / max);
    return adjMap;
}

class Expander
{
public:
    std::vector<int> steps;
    int rows, cols;
    Expander(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;
        steps.push_back(0); steps.push_back(-1); steps.push_back(1); 
    }

    std::vector<Point> expand(Point st)
    {
        std::vector<Point> res;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                if (i !=0 || j != 0)
                {
                    Point tmp(st.X + this->steps[i], st.Y + this->steps[j]);
                    if(tmp.X > -1 && tmp.Y > -1 && tmp.X < this->rows && tmp.Y < this->cols)
                        res.push_back(tmp);
                }
        return res;
    }
};

Component searchComponent(Point st, cv::Mat const &map, cv::Mat const &mask, Expander &expander, int threshold)
{
    Component com;
    std::queue<Point> qu;
    qu.push(st);
    com.points.push_back(st);
    while(!qu.empty())
    {
        Point t = qu.front();
        qu.pop();
        auto new_points = expander.expand(t);
        for(auto it = new_points.begin(); it != new_points.end(); it++)
        {
            if ((mask.data[it->X*map.cols + it->Y] == 0) && (abs(map.at<AT_TYPE>(t.X, t.Y) - map.at<AT_TYPE>(it->X, it->Y)) < threshold)) 
            {
                com.points.push_back(*it);
                mask.data[it->X*map.cols + it->Y] = 1;
                qu.push(*it);
            }
        }
    }
    com.X1 = INT_MAX;
    com.Y1 = INT_MAX;
    com.X2 = 0;
    com.Y2 = 0;
    double sum = 0;
    for(auto it = com.points.begin(); it != com.points.end(); it++)
    {
        if(it->X > com.X2) com.X2 = it->X;
        if(it->X < com.X1) com.X1 = it->X;
        if(it->Y > com.Y2) com.Y2 = it->Y;
        if(it->Y < com.Y1) com.Y1 = it->Y;
        sum += map.data[it->X*map.cols + it->Y];
    }
    double somemean = sum/com.points.size();
    sum = 0;
    for(auto it = com.points.begin(); it != com.points.end(); it++)
    {
        sum += pow(map.data[it->X*map.cols + it->Y], 2) - pow(somemean, 2);
    }
    com.std = sum/(com.points.size() - 1);
    com.mean = somemean;
    com.width = com.Y2 - com.Y1;
    com.height = com.X2 - com.X1;
    return com;
}

std::vector<Component> associate(cv::Mat const &depth_map, int threshold)
{
    Expander expander(depth_map.rows, depth_map.cols);
    cv::Mat mask = cv::Mat::zeros(depth_map.rows, depth_map.cols, cv::DataType<bool>::type);
    std::vector<Component> components;
    for(int i = 0; i < depth_map.rows; i++)
    {
        for(int j = 0; j < depth_map.cols; j++)
        {
            if (mask.data[i*depth_map.cols + j] == 0)
            {
                mask.data[i*depth_map.cols + j] = 1;
                Component tmp = searchComponent(Point(i, j), depth_map, mask, expander, threshold);
                if (tmp.points.size() > 5) components.push_back(tmp);
            }
        }
    }
    return components;
}

cv::Mat getDepthMap(cv::Mat const &left, cv::Mat const &right)
{
    cv::Mat res; 
    cv::StereoBM bm(CV_STEREO_BM_NORMALIZED_RESPONSE);
    bm(left, right, res);
    //std::cout<<res;
    return res;
}

cv::Mat getDepthMapVar(cv::Mat const &left, cv::Mat const &right)
{
    cv::Mat res;
    cv::StereoVar var;
    var.levels = 3; // ignored with USE_AUTO_PARAMS (!)
    var.pyrScale = 0.5;                             // ignored with USE_AUTO_PARAMS
    var.nIt = 25;
    var.minDisp = ((left.cols/8) + 15) & -16;
    var.maxDisp = 0;
    //var.poly_n = 3;
    var.poly_n = 9;
    //var.poly_sigma = 0.0;
    var.poly_sigma = 1.7;
    var.fi = 15.0f;//nice
    var.lambda = 0.04f;
    var.penalization = var.PENALIZATION_TICHONOV;   // ignored with USE_AUTO_PARAMS
    var.cycle = var.CYCLE_V;                        // ignored with USE_AUTO_PARAMS
    var.flags = var.USE_SMART_ID | var.USE_AUTO_PARAMS | var.USE_INITIAL_DISPARITY | var.USE_MEDIAN_FILTERING ;

    var(left, right, res);
    /*for(int i = 0; i < left.rows; i++)
    {
        for(int j = 0; j < left.cols; j++)
        {
            std::cout<<(short)res.at<char>(i, j)<<" ";
        }
    }
    std::cout<<res;*/
    return res;
}

int main(int argc, char **argv) {
    auto left_name  = "tsukuba/scene1.row3.col3.ppm";
    auto right_name = "tsukuba/scene1.row3.col5.ppm";
    if (argc > 2)
    {
        left_name = argv[1];
        right_name = argv[2];
    }
    cv::Mat left  = cv::imread(left_name, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat right = cv::imread(right_name, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat map = (getDepthMap(left, right));
    //cv::Mat map = (getDepthMapVar(left, right));
    //exit(0);
    auto components = associate((map), 1);//10 2

    cv::Mat res = cv::Mat::zeros(map.rows, map.cols, map.type());
    std::cout<<"Num of components:>>>"<<components.size()<<std::endl;
    std::cout<<"d "<<map.depth()<<" c " <<map.channels()<<" t "<<map.type()<<"\n";
    for(auto it = components.begin(); it != components.end(); it++)
    {
        if (it->points.size() < 30) continue;
        res = cv::Mat::zeros(map.rows, map.cols, map.type());
        for(auto it2 = it->points.begin(); it2 != it->points.end(); it2++)
        {
            //res.data[it2->X * res.cols + it2->Y] = 200;
            res.at<AT_TYPE>(it2->X, it2->Y) = 200;
        }
        //cv::rectangle(res, cv::Point(it->Y2, it->X2), cv::Point(it->Y1, it->X1), cv::Scalar(220), -1, 8);
        std::cout<<"w"<<it->width<<" h"<<it->height<<" std "<<it->std<<" mean "<<it->mean<<" s/m "<<it->std/it->mean<<"\n";
        cv::imshow("i ", normalize(res));
        cv::imshow("Out", normalize(map));
        cv::waitKey();
    }

    cv::imshow("i ", normalize(res));
    cv::imshow("Out", map);
    cv::imshow("left", left);
    cv::imshow("right", right);

    while (cv::waitKey() % 0x100 != 27){};
    return 0;
}
