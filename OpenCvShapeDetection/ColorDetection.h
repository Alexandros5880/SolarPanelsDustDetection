#ifndef GENERAL_H
#include "General.h"
#endif

//using namespace cv;
using namespace std;

class ColorDetection {
public:
    void color_detection_on_video();
    void color_detection_on_image(
        cv::Mat* imgOriginal,
        cv::Mat* imgThresholded,
        cv::Scalar* LowHSV,
        cv::Scalar* HightHSV,
        cv::Size* thresholdedSize
    );
private:
    void crop_black_borders(cv::Mat* image);
    bool detect_black_pixels(cv::Mat* image);
    bool detect_white_pixels(cv::Mat* image);
};