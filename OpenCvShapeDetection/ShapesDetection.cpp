#include "./ShapesDetection.h"

MyCountours::MyCountours(
    vector<vector<cv::Point>> contours,
    vector<cv::Vec4i> hierarchy
) {
    this->contours = contours;
    this->hierarchy = hierarchy;
}

cv::Mat ShapeDetection::get_gray(cv::Mat *frame) {
    cv::Mat gray;
    cv::cvtColor(*frame, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

cv::Mat ShapeDetection::get_countours_frame(cv::Mat *frame_gray)
{
    int thresh = 100;
    cv::Mat canny_output;
    cv::Canny(*frame_gray, canny_output, thresh, thresh * 2);
    vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
    findContours(canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    cv::RNG rng(12345);
    cv::Mat drawing_countours_image = cv::Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing_countours_image, contours, (int)i, color, 2, cv::LINE_8, hierarchy, 0);
    }

    return drawing_countours_image;
}

cv::Mat ShapeDetection::get_squares_with_gradient_shading(cv::Mat *gray) {
    cv::Mat bw;
    blur(*gray, bw, cv::Size(3, 3));
    cv::Canny(*gray, bw, 80, 240, 3);
    return bw;
}

void ShapeDetection::get_squares(cv::Mat* image, cv::Mat* imageOutput) {
    cv::Mat bw = get_squares_with_gradient_shading(image);
    *imageOutput = get_countours_frame(image);
}
