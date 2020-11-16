#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;


int main()
{
    cv::Mat image = cv::imread("error.png", 0);// read the file
    cv::namedWindow( "Display window", WINDOW_AUTOSIZE );// create a window for display.
    cv::imshow( "Display window", image );// show our image inside it.
    cv::waitKey(0);// wait for a keystroke in the window
    return 0;
}



    