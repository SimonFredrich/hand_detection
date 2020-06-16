#ifndef _HAND_GESTURE_
#define _HAND_GESTURE_

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

class HandMasker
{
private:
    Scalar hand_tresh;
    Mat hand_mask;
    void thresh_search(Mat &input_img);
    void draw_search(Mat &input_img);

public:
    Mat process(Mat &input_img);
};

#endif