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
    Scalar upper_hand_thresh;
    Scalar lower_hand_thresh;
    Mat hand_mask;
    Mat output_img;
    void thresh_search(Mat &input_img);
    void draw_search(Mat &input_img);

public:
    Mat process(Mat &input_img);
};

#endif