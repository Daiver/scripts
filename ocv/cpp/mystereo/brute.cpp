#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <vector>
#include <queue>
#include <fstream>
#include <stdio.h>

cv::Mat normalize(cv::Mat const &depth_map)
{
    double min;
    double max;
    cv::minMaxIdx(depth_map, &min, &max);
    cv::Mat adjMap;
    cv::convertScaleAbs(depth_map, adjMap, 255 / max);
    return adjMap;
}

void bruteDepthMapBM(cv::Mat const &left_c, cv::Mat const &right_c)
{
    cv::StereoBM bm;
    static int frame_num = 0;
    frame_num += 1;
    cv::Mat left, right;
    cv::cvtColor(left_c, left, CV_RGB2GRAY);
    cv::cvtColor(right_c, right, CV_RGB2GRAY);
    for(int sadSize = 5; sadSize < 20; sadSize += 2)
    {
        for(int uniquenessRatio = 5; uniquenessRatio < 25; uniquenessRatio += 5)
        {
            for (int speckleWindowSize = 50; speckleWindowSize < 200; speckleWindowSize += 25)
            {
                bm.state->preFilterCap = 31;
                //bm.state->SADWindowSize = 9;
                bm.state->SADWindowSize = sadSize;
                bm.state->minDisparity = 0;
                bm.state->numberOfDisparities =  ((left.cols/8) + 15) & -16;
                bm.state->textureThreshold = 10;
                //bm.state->uniquenessRatio = 15;
                bm.state->uniquenessRatio = uniquenessRatio;
                //bm.state->speckleWindowSize = 100;
                bm.state->speckleWindowSize = speckleWindowSize;
                bm.state->speckleRange = 32;
                bm.state->disp12MaxDiff = 1;
                cv::Mat res;
                bm(left, right, res); 
                char buf[512];
                sprintf(buf, "dumps/num%d_sadsize%d_uniq%d_speckle%d.jpg", frame_num, sadSize, uniquenessRatio, speckleWindowSize);
                cv::imwrite(buf, res);
                cv::imshow("", normalize(res));
                cv::waitKey(1);
            }
        }
    }
}

void bruteDepthMapVar(cv::Mat const &left_c, cv::Mat const &right_c)
{
    static int frame_num = 0;
    frame_num += 1;
    cv::Mat left, right;
    cv::cvtColor(left_c, left, CV_RGB2GRAY);
    cv::cvtColor(right_c, right, CV_RGB2GRAY);
    for(int nIt = 25; nIt < 200; nIt += 20)
    {
        for(int poly_n = 3; poly_n < 10; poly_n += 2)
        {
            for(int poly_sigma_c = 0; poly_sigma_c < 20; poly_sigma_c += 2)
            {
                for(int fi_c = 5; fi_c < 50; fi_c += 5)
                {
                    cv::StereoVar var;
                    var.nIt = nIt;
                    
                    var.minDisp = ((left.cols/8) + 15) & -16;
                    var.maxDisp = 0;

                    var.poly_n = poly_n;
                    var.poly_sigma = 0.1 * poly_sigma_c;
                    //var.fi = 15.0f;//nice
                    var.fi = fi_c*1.0;
                    var.lambda = 0.04f;

                    var.penalization = var.PENALIZATION_TICHONOV;   // ignored with USE_AUTO_PARAMS
                    var.cycle = var.CYCLE_V;                        // ignored with USE_AUTO_PARAMS
                    var.flags = var.USE_SMART_ID | var.USE_AUTO_PARAMS | var.USE_INITIAL_DISPARITY | var.USE_MEDIAN_FILTERING ;
                    var.levels = 3; // ignored with USE_AUTO_PARAMS (!)
                    var.pyrScale = 0.5;                             // ignored with USE_AUTO_PARAMS
                    cv::Mat res;
                    var(left, right, res);
                    char buf[512];
                    sprintf(buf, "dumps/fn%d_nIt%d_polyn_%d_polyn_sigma%f_fi%d.jpg", frame_num, nIt, poly_n, poly_sigma_c * 0.1, fi_c);
                    cv::imwrite(buf, res);
                }
            }
        }
    }
    std::cout<<frame_num<<"\n";
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
    return res;
}

cv::Mat getDepthMapBM(cv::Mat const &left, cv::Mat const &right)
{
    cv::Mat res; 
    cv::StereoBM bm(CV_STEREO_BM_NORMALIZED_RESPONSE);
    //cv::StereoBM bm(CV_STEREO_BM_NARROW);
    bm(left, right, res);
    return res;
}


void videoWork(int argc, char**argv)
{
    if(argc < 3)
    {
        std::cout<<"Wrong num of args"<<std::endl;
        return;
    }
    cv::VideoCapture Lcap(argv[1]);
    cv::VideoCapture Rcap(argv[2]);
    if (!Lcap.isOpened() || !Rcap.isOpened())
    {
        std::cout  << "Could not open reference " << argv[1] << std::endl;
        std::cout  << "Could not open reference " << argv[2] << std::endl;
        return ;
    }
    cv::Mat frame1;
    cv::Mat frame2;
    cv::Mat oldL;
    while(1)
    {
        Lcap >> frame1;
        Rcap >> frame2;
        if (frame1.empty()) break;
        bruteDepthMapBM(frame1, frame2);
        //bruteDepthMapVar(frame1, frame2);
    }
}

void photoWork(int argc, char** argv)
{
    auto left_name  = "tsukuba/scene1.row3.col3.ppm";
    auto right_name = "tsukuba/scene1.row3.col5.ppm";
    if (argc > 2)
    {
        left_name = argv[1];
        right_name = argv[2];
    }
    cv::Mat left  = cv::imread(left_name);
    cv::Mat right = cv::imread(right_name);
    bruteDepthMapBM(left, right);
   // bruteDepthMapVar(left, right);
}

int main(int argc, char **argv)
{
    if(argc > 1 && (strcmp(argv[1], "-v") == 0))
    {
        std::cout<<"Video"<<std::endl;
        videoWork(argc-1, argv+1);
    }
    else
    {
        std::cout<<"Photo"<<std::endl;
        photoWork(argc, argv);
    }
    return 0;
}
