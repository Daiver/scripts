#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <ctype.h>

#include "lktracker.h"

using namespace cv;
using namespace std;

static void help()
{
    // print a welcome message, and the OpenCV version
    cout << "\nThis is a demo of Lukas-Kanade optical flow lkdemo(),\n"
            "Using OpenCV version " << CV_VERSION << endl;
    cout << "\nIt uses camera by default, but you can provide a path to video as an argument.\n";
    cout << "\nHot keys: \n"
            "\tESC - quit the program\n"
            "\tr - auto-initialize tracking\n"
            "\tc - delete all the points\n"
            "\tn - switch the \"night\" mode on/off\n"
            "To add/remove a feature point click it\n" << endl;
}

int main( int argc, char** argv )
{
    help();

    VideoCapture cap;
    bool needToInit = false;
    bool nightMode = false;

    if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
        cap.open(argc == 2 ? argv[1][0] - '0' : 0);
    else if( argc == 2 )
        cap.open(argv[1]);

    if( !cap.isOpened() )
    {
        cout << "Could not initialize capturing...\n";
        return 0;
    }

    namedWindow( "LK Demo", 1 );

    Mat gray, image, frame, r_frame;
    cap >> frame;
    frame.copyTo(image);
    cvtColor(image, gray, COLOR_BGR2GRAY);
    LKTracker tracker;

    cv::Rect roi(200, 120, 100, 150);
    r_frame = cv::Mat(gray, roi);

    tracker.init(r_frame);
    for(;;)
    {
        cap >> frame;
        if( frame.empty() )
            break;

        frame.copyTo(image);
        cvtColor(image, gray, COLOR_BGR2GRAY);

        if( nightMode )
            image = Scalar::all(0);

        r_frame = cv::Mat(gray, roi);
        if( needToInit )
            tracker.init(r_frame);

        cv::rectangle(image, roi, cv::Scalar(0, 0, 255));

        bool is_good;
        auto pt = tracker.track(r_frame, &is_good);
        if (is_good)
            for(auto p : pt)
            {
                circle( image, cv::Point2f(p.x + roi.x, p.y + roi.y), 3, Scalar(0,255,0), -1, 8);
            }
    
        needToInit = false;
        imshow("LK Demo", image);

        char c = (char)waitKey(10);
        if( c == 27 )
            break;
        switch( c )
        {
        case 'r':
            needToInit = true;
            break;
        case 'c':
            break;
        case 'n':
            nightMode = !nightMode;
            break;
        }
    }

    return 0;
}
