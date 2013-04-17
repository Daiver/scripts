#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <vector>
#include <queue>

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
    int X1, X2, Y1, Y2, width, height, centerX, centerY;
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
            //if ((mask.data[it->X*map.cols + it->Y] == 0) && (abs(map.data[t.X*map.cols + t.Y] - map.data[it->X*map.cols + it->Y]) < threshold)) 
            if ((mask.data[it->X*map.cols + it->Y] == 0) && (abs(map.at<uchar>(t.X, t.Y) - map.at<uchar>(it->X, it->Y)) < threshold)) 
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
    com.centerX = com.X1 + com.height/2;
    com.centerY = com.Y1 + com.width/2;
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

cv::Mat getDepthMapVar(cv::Mat const &left, cv::Mat const &right)
{
    cv::Mat res;
    cv::StereoVar var;
    var.levels = 3; // ignored with USE_AUTO_PARAMS (!)
    var.pyrScale = 0.5;                             // ignored with USE_AUTO_PARAMS
    var.nIt = 25;
    var.minDisp = ((left.cols/8) + 15) & -16;
    var.maxDisp = 0;
    var.poly_n = 3;
    var.poly_sigma = 0.0;
    var.fi = 15.0f;//nice
    var.lambda = 0.03f;
    var.penalization = var.PENALIZATION_TICHONOV;   // ignored with USE_AUTO_PARAMS
    var.cycle = var.CYCLE_V;                        // ignored with USE_AUTO_PARAMS
    var.flags = var.USE_SMART_ID | var.USE_AUTO_PARAMS | var.USE_INITIAL_DISPARITY | var.USE_MEDIAN_FILTERING ;

    var(left, right, res);
    return res;
}

cv::Mat getDepthMapBM(cv::Mat const &left, cv::Mat const &right)
{
    cv::Mat res; 
    cv::StereoBM bm(CV_STEREO_BM_NORMALIZED_RESPONSE);
    bm(left, right, res);
    return res;
}

void showComponents(std::vector<Component> &components, cv::Mat map)
{
    cv::Mat res = cv::Mat::zeros(map.rows, map.cols, map.type());
    std::cout<<"Num of components:>>>"<<components.size()<<std::endl;
    for(auto it = components.begin(); it != components.end(); it++)
    {
        if (it->points.size() < 30) continue;
        res = cv::Mat::zeros(map.rows, map.cols, map.type());
        for(auto it2 = it->points.begin(); it2 != it->points.end(); it2++)
        {
            res.at<uchar>(it2->X, it2->Y) = 200; //short
        }
        std::cout<<"s "<<it->points.size()<<" w"<<it->width<<" h"<<it->height<<" cX "<<it->centerX<<" cY "<<it->centerY<<" std "<<it->std<<" mean "<<it->mean<<" s/m "<<it->std/it->mean<<"\n";
        cv::imshow("i ", normalize(res));
        cv::waitKey();
    }

    cv::imshow("i ", normalize(res));
    cv::imshow("Out", map);

}

void work(cv::Mat &left, cv::Mat &right)
{
    cv::Mat map = (getDepthMapBM(left, right));
    //cv::Mat map = (getDepthMapVar(left, right));
    
    cv::imshow("left", left);
    cv::imshow("right", right);
    auto components = associate(normalize(map), 2);//10 2
    map = normalize(map);
    cv::imshow("Out", map);
    //showComponents(components, map);

}

int main(int argc, char **argv) {
    std::cout<<argv[1]<<std::endl;
    cv::VideoCapture Lcap(argv[1]);
    cv::VideoCapture Rcap(argv[2]);
    if (!Lcap.isOpened() || !Rcap.isOpened())
    {
        std::cout  << "Could not open reference " << argv[1] << std::endl;
        std::cout  << "Could not open reference " << argv[2] << std::endl;
        return -1;
    }
    cv::Mat frame1;
    cv::Mat frame2;
    while(1)
    {
        Lcap >> frame1;
        Rcap >> frame2;
        if (frame1.empty()) break;
        cv::imshow("1", frame1);    
        cv::imshow("2", frame2);    
        cv::cvtColor(frame1, frame1, CV_RGB2GRAY);
        cv::cvtColor(frame2, frame2, CV_RGB2GRAY);
        work(frame1, frame2);
        cv::waitKey(1);
    }
    /*auto left_name  = "tsukuba/scene1.row3.col3.ppm";
    auto right_name = "tsukuba/scene1.row3.col5.ppm";
    if (argc > 2)
    {
        left_name = argv[1];
        right_name = argv[2];
    }
    cv::Mat left  = cv::imread(left_name, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat right = cv::imread(right_name, CV_LOAD_IMAGE_GRAYSCALE);
    work(left, right);*/
    while (cv::waitKey() % 0x100 != 27){};
    return 0;
}
