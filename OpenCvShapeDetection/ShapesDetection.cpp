#include "./ShapesDetection.h"

MyCountours::MyCountours(
    vector<vector<cv::Point>> contours,
    vector<cv::Vec4i> hierarchy
) {
    this->contours = contours;
    this->hierarchy = hierarchy;
}

cv::Mat get_gray(cv::Mat *frame) {
    cv::Mat gray;
    cv::cvtColor(*frame, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

cv::Mat get_countours_frame(cv::Mat *frame_gray)
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

cv::Mat get_squares_with_gradient_shading(cv::Mat *gray) {
    cv::Mat bw;
    blur(*gray, bw, cv::Size(3, 3));
    cv::Canny(*gray, bw, 80, 240, 3);
    return bw;
}

void createTestImage() {
    cv::Mat image = cv::Mat::zeros(300, 600, CV_8UC3);
    circle(image, cv::Point(250, 150), 100, cv::Scalar(0, 255, 128), -100);
    circle(image, cv::Point(350, 150), 100, cv::Scalar(255, 255, 255), -100);
    imshow("Display Window", image);
    cv::waitKey(0);
}

void shape_detection_example() {
    //cv::Mat frame = cv::imread("polygon.png");
    cv::Mat frame;
    cv::Mat gray;
    cv::Mat bw;
    cv::Mat drawing_countours_frame;

    cv::VideoCapture capture(0);
    int q;

    while (cv::waitKey(30) != 'q')
    {
        capture >> frame;

        // Convert to grayscale
        gray = get_gray(&frame);

        // Use Canny instead of threshold to catch squares with gradient shading
        bw = get_squares_with_gradient_shading(&gray);

        // Get Countours
        drawing_countours_frame = get_countours_frame(&gray);

        cv::imshow("bw", bw);
        cv::imshow("frame", frame);
        cv::imshow("gray", gray);
        cv::imshow("Contours", drawing_countours_frame);
    }
}