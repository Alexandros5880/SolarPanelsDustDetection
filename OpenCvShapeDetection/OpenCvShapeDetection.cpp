#include "./General.h"
#include "./ShapesDetection.h"
#include "./ColorDetection.h"

//using namespace cv;
using namespace std;

const char* image_path; // = "C:\\Users\\Alexp\\OneDrive\\Desktop\\Solar_Panels_Images\\5.webp";


// Create Collor Satuation Controll Window
int iLowH = 31;
int iHighH = 130;

int iLowS = 95;
int iHighS = 255;

int iLowV = 28;
int iHighV = 123;

cv::Scalar LowHSV;
cv::Scalar HightHSV;
// || Create Collor Satuation Controll Window



int main(int argc, char** argv)
{
    image_path = argv[1];

    ColorDetection colorDetection = ColorDetection();
    ShapeDetection shapeDetection = ShapeDetection();

    cv::Mat imgThresholded;
    cv::Mat imgSquares;
    cv::Mat imgOriginal = cv::imread(image_path, cv::IMREAD_COLOR);
    cv::Size thresholdedSize = cv::Size(1, 1);

    // Create Collor Satuation Controll Window
    cv::namedWindow("Control", cv::WINDOW_AUTOSIZE);
    // Hue (0 - 179)
    cv::createTrackbar("LowH", "Control", &iLowH, 179);
    cv::createTrackbar("HighH", "Control", &iHighH, 179);
    // Saturation (0 - 255)
    cv::createTrackbar("LowS", "Control", &iLowS, 255);
    cv::createTrackbar("HighS", "Control", &iHighS, 255);
    // Value (0 - 255)
    cv::createTrackbar("LowV", "Control", &iLowV, 255);
    cv::createTrackbar("HighV", "Control", &iHighV, 255);
    // || Create Collor Satuation Controll Window

    while (cv::waitKey(30) != 'q') {
        // Create Low And Hight Collor Values
        LowHSV = cv::Scalar(iLowH, iLowS, iLowV);
        HightHSV = cv::Scalar(iHighH, iHighS, iHighV);
        cout << "LowHSV: " << LowHSV << " HightHSV: " << HightHSV << endl;
        // || Create Collor Satuation Controll Window

        colorDetection.color_detection_on_image(&imgOriginal , &imgThresholded, &LowHSV, &HightHSV, &thresholdedSize);
        shapeDetection.get_squares(&imgThresholded, &imgSquares);

        cv::imshow("Image", imgOriginal);
        cv::imshow("Thresholded Image", imgThresholded);
        cv::imshow("Squares Image", imgSquares);
    }

    return 0;
}
