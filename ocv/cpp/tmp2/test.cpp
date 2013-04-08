//
// for testing
//
// robocraft.ru
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
        IplImage* image=0, *dst=0;
        char filename[] = "Image0.jpg";
        image = cvLoadImage(filename, 1);
        printf("[i] image: %s\n", filename);
        assert( image != 0 );
        cvNamedWindow( "image");
        cvShowImage( "image", image );
        cvWaitKey(0);
        cvReleaseImage(& image);
        cvReleaseImage(&dst);

        // удаляем окна
        cvDestroyAllWindows();
        return 0;
}
