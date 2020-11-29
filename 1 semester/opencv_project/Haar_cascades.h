//
// Created by nalexx on 29.11.20.
//

#ifndef OPENCV_PROJECT_HAAR_CASCADES_H
#define OPENCV_PROJECT_HAAR_CASCADES_H

#include <iostream>
#include <opencv2/opencv.hpp>

class Haar_cascades {


private:

    cv::CascadeClassifier face_cascade;
    cv::CascadeClassifier eyes_cascade;

    void detectAndDisplay(cv::Mat frame );



public:

    Haar_cascades() = default;
    ~Haar_cascades() = default;

    int run();

};


#endif //OPENCV_PROJECT_HAAR_CASCADES_H
