#include "HandMasker.hpp"
using namespace std;
using namespace cv;

Mat HandMasker::process(Mat &input_img)
{
    cout << "Starting HandMasker processing..." << endl;

    // output
    input_img.copyTo(output_img);

    // threshold samples
    thresh_search(output_img);
    // threshold sample areas
    draw_search(output_img);

    return output_img;
}

/**
 * Maskierung der in den Parametern 
 * befindlichen Objekte
 * 
 * @param input_img
 * @return nothing
 */
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
    Vec3b hotspot_3 = input_img.at<Vec3b>(h / 1.5, w / 2);
    Vec3b hotspot_4 = input_img.at<Vec3b>(h / 2, w / (5.0 / 2));
    Vec3b hotspot_5 = input_img.at<Vec3b>(h / 2, w / (5.0 / 3));

    int hues[5] = {
        (int)hotspot_1.val[0],
        (int)hotspot_2.val[0],
        (int)hotspot_3.val[0],
        (int)hotspot_4.val[0],
        (int)hotspot_5.val[0]};

    int highest_hue = hues[0];
    int lowest_hue = hues[0];
    for (size_t i = 1; i < 5; i++)
    {
        if (hues[i] > highest_hue)
            highest_hue = hues[i];
        if (hues[i] < lowest_hue)
            lowest_hue = hues[i];
    }

    upper_hand_thresh = Scalar(highest_hue + 10, 255, 255);
    lower_hand_thresh = Scalar(lowest_hue - 10, 50, 50);

    inRange(input_img, Scalar(lower_hand_thresh), Scalar(upper_hand_thresh), output_img);
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