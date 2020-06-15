#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include "HandMasker.hpp"
using namespace cv;
using namespace std;

int main(int, char **)
{
    HandMasker hand_masker;

    //--- INITIALIZE FRAME AND VIDEOCAPTURE
    Mat frame;
    VideoCapture cap;

    // defining video stream sources
    const int camera_index = 0;

    // open camera streams
    cap.open(camera_index);

    // check if we succeeded
    if (!cap.isOpened())
    {
        cerr << "ERROR! Unable to open stationary camera\n";
        return -1;
    }

    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
         << "Press any key to terminate" << endl;
    for (;;)
    {
        // wait for a new frame from camera and store it into frame
        cap >> frame;

        // check if we succeeded
        if (frame.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        Mat proc_frame = hand_masker.processing(frame);

        // show frames live
        imshow("Original", frame);
        imshow("Processed", proc_frame);

        if (waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}