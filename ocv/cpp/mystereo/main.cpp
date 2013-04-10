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

class Component
{
public:
    std::vector<Point> points;
    int X1, X2, Y1, Y2;
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

Component searchComponent(Point st, cv::Mat const &map, cv::Mat const &mask, Expander &expander)
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
            if ((mask.data[it->X*map.cols + it->Y] == 0) && (abs(map.data[t.X*map.cols + t.Y] - map.data[it->X*map.cols + it->Y]) < 2))//10 for original
            {
                com.points.push_back(*it);
                mask.data[it->X*map.cols + it->Y] = 1;
                qu.push(*it);
            }
        }
    }
    return com;
}

void someWork(cv::Mat const &depth_map)
{
    Expander expander(depth_map.rows, depth_map.cols);
    cv::Mat mask = cv::Mat::zeros(depth_map.rows, depth_map.cols, cv::DataType<bool>::type);
    //std::cout<<depth_map<<"\n";
    std::cout<<">"<<depth_map.rows<<" "<<depth_map.cols<<"\n";
    std::cout<<">"<<mask.rows<<" "<<mask.cols<<"\n";
    std::vector<Component> components;
    cv::Mat res = cv::Mat::zeros(depth_map.rows, depth_map.cols, depth_map.type());
    for(int i = 0; i < depth_map.rows; i++)
    {
        for(int j = 0; j < depth_map.cols; j++)
        {
            if (mask.data[i*depth_map.cols + j] == 0)
            {
                mask.data[i*depth_map.cols + j] = 1;
                Component tmp = searchComponent(Point(i, j), depth_map, mask, expander);
                if (tmp.points.size() > 5) components.push_back(tmp);
            }
        }
    }
    std::cout<<"\n>>>"<<components.size()<<std::endl;
    for(auto it = components.begin(); it != components.end(); it++)
    {
        if (it->points.size() < 1) continue;
        for(auto it2 = it->points.begin(); it2 != it->points.end(); it2++)
        {
            res.data[it2->X * res.cols + it2->Y] = 200;
        }
        cv::imshow("i ", normalize(res));
        cv::waitKey();
    }
    cv::imshow("i ", normalize(res));
}

cv::Mat getDepthMap(cv::Mat const &left, cv::Mat const &right)
{
    cv::Mat res; 
    cv::StereoBM bm(CV_STEREO_BM_NORMALIZED_RESPONSE);
    bm(left, right, res);
    return res;
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
    someWork(normalize(map));
    cv::Mat adjMap = normalize(map);
    cv::imshow("Out", adjMap);

    cv::imshow("left", left);
    cv::imshow("right", right);
    while (cv::waitKey() % 0x100 != 27){};

    return 0;
}
