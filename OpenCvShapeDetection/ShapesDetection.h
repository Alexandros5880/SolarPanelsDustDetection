#ifndef GENERAL_H
#include "General.h"
#endif

//using namespace cv;
using namespace std;

class ShapeDetection {
public:
    void get_squares(cv::Mat* image, cv::Mat* imageOutput);
private:
    cv::Mat get_gray(cv::Mat* frame);
    cv::Mat get_squares_with_gradient_shading(cv::Mat* gray);
    cv::Mat get_countours_frame(cv::Mat* frame_gray);
};

class MyCountours {
public:
    MyCountours(
        vector<vector<cv::Point> > contours,
        vector<cv::Vec4i> hierarchy
    );
    vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
};
