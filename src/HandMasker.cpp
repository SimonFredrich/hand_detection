#include "HandMasker.hpp"
using namespace std;
using namespace cv;

Mat HandMasker::process(Mat &input_img)
{
    cout << "Starting HandMasker processing..." << endl;

    // output
    Mat output_img;
    input_img.copyTo(output_img);

    // threshold samples
    thresh_search(output_img);
    // threshold sample areas
    draw_search(output_img);

    return output_img;
}

void HandMasker::thresh_search(Mat &input_img)
{
    // Image dimensions
    int h = input_img.size().height;
    int w = input_img.size().width;

    Mat HSV_img;
    cvtColor(input_img, HSV_img, COLOR_RGB2HSV);

    // Save color samples
    Vec3b hotspot_1 = input_img.at<Vec3b>(h / 2, w / 2);
    int H_hs_1 = (int)hotspot_1.val[0];
    int S_hs_1 = (int)hotspot_1.val[1];
    int V_hs_1 = (int)hotspot_1.val[2];
    Vec3b hotspot_2 = input_img.at<Vec3b>(h / 3, w / 2);
    int H_hs_2 = (int)hotspot_1.val[0];
    int S_hs_2 = (int)hotspot_1.val[1];
    int V_hs_2 = (int)hotspot_1.val[2];
    Vec3b hotspot_3 = input_img.at<Vec3b>(h / 1.5, w / 2);
    int H_hs_3 = (int)hotspot_1.val[0];
    int S_hs_3 = (int)hotspot_1.val[1];
    int V_hs_3 = (int)hotspot_1.val[2];
    Vec3b hotspot_4 = input_img.at<Vec3b>(h / 2, w / (5.0 / 2));
    int H_hs_4 = (int)hotspot_1.val[0];
    int S_hs_4 = (int)hotspot_1.val[1];
    int V_hs_4 = (int)hotspot_1.val[2];
    Vec3b hotspot_5 = input_img.at<Vec3b>(h / 2, w / (5.0 / 3));
    int H_hs_5 = (int)hotspot_1.val[0];
    int S_hs_5 = (int)hotspot_1.val[1];
    int V_hs_5 = (int)hotspot_1.val[2];
}

void HandMasker::draw_search(Mat &input_img)
{
    // Image dimensions
    int w = input_img.size().width;
    int h = input_img.size().height;

    // Rect dimensions
    int rect_side = 16;

    // Indication where the color samples are made
    // hotspot 1
    rectangle(input_img, Rect(w / 2 - rect_side / 2, h / 2 - rect_side / 2, rect_side, rect_side), Scalar(0, 255, 0), 1);
    // hotspot 2
    rectangle(input_img, Rect(w / 2 - rect_side / 2, h / 3 - rect_side / 2, rect_side, rect_side), Scalar(0, 255, 0), 1);
    // hotspot 3
    rectangle(input_img, Rect(w / 2 - rect_side / 2, h / 1.5 - rect_side / 2, rect_side, rect_side), Scalar(0, 255, 0), 1);
    // hotspot 4
    rectangle(input_img, Rect(w / (5.0 / 2) - rect_side / 2, h / 2 - rect_side / 2, rect_side, rect_side), Scalar(0, 255, 0), 1);
    // hotspot 5
    rectangle(input_img, Rect(w / (5.0 / 3) - rect_side / 2, h / 2 - rect_side / 2, rect_side, rect_side), Scalar(0, 255, 0), 1);
}