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
    draw_search(input_img);

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
    cvtColor(input_img, HSV_img, COLOR_BGR2HSV);

    // Save color samples
    int hotspot_1 = (int)HSV_img.at<Vec3b>(h / 2, w / 2).val[0];
    int hotspot_2 = (int)HSV_img.at<Vec3b>(h / 3, w / 2).val[0];
    int hotspot_3 = (int)HSV_img.at<Vec3b>(h / 1.5, w / 2).val[0];
    int hotspot_4 = (int)HSV_img.at<Vec3b>(h / 2, w / (5.0 / 2)).val[0];
    int hotspot_5 = (int)HSV_img.at<Vec3b>(h / 2, w / (5.0 / 3)).val[0];

    cout << hotspot_1 << endl;

    Scalar upper_thresholds[5] = {
        Scalar(hotspot_1 + 10, 255, 255),
        Scalar(hotspot_2 + 10, 255, 255),
        Scalar(hotspot_3 + 10, 255, 255),
        Scalar(hotspot_4 + 10, 255, 255),
        Scalar(hotspot_5 + 10, 255, 255),
    };

    Scalar lower_thresholds[5] = {
        Scalar(hotspot_1 - 10, 100, 100),
        Scalar(hotspot_2 - 10, 100, 100),
        Scalar(hotspot_3 - 10, 100, 100),
        Scalar(hotspot_4 - 10, 100, 100),
        Scalar(hotspot_5 - 10, 100, 100),
    };

    //Mat thresh_imgs[5];
    array<Mat, 5> thresh_imgs;

    // Create all the individual thresholds
    for (size_t i = 0; i < thresh_imgs.size(); i++)
    {
        inRange(input_img, lower_thresholds[i], upper_thresholds[i], thresh_imgs[i]);
    }

    cout << thresh_imgs[0] << endl;

    // unite thresholds
    for (size_t i = 1; i < thresh_imgs.size(); i++)
    {
        for (size_t row = 0; row < thresh_imgs[i].rows; row++)
        {
            for (size_t col = 0; col < thresh_imgs[i].cols; col++)
            {
                int pixel = (int)thresh_imgs[i].at<uchar>(row, col);
                if (pixel != 0)
                {
                    thresh_imgs[0].at<uchar>(row, col) = 255;
                }
            }
        }
    }

    output_img = thresh_imgs[0];
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