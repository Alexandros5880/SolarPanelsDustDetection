#include "./ColorDetection.h"

void ColorDetection::color_detection_on_image(
    cv::Mat* imgOriginal,
    cv::Mat* imgThresholded,
    cv::Scalar* LowHSV,
    cv::Scalar* HightHSV,
    cv::Size* thresholdedSize
) {
    crop_black_borders(imgOriginal);
    cv::Mat imgHSV;
    cv::cvtColor(*imgOriginal, imgHSV, cv::COLOR_BGR2HSV); // Convert the captured frame from BGR to HSV
    cv::inRange(imgHSV, *LowHSV, *HightHSV, *imgThresholded); // Threshold the image
    // morphological opening (remove small objects from the foreground)
    cv::erode(*imgThresholded, *imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, *thresholdedSize));
    cv::dilate(*imgThresholded, *imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, *thresholdedSize));
    // morphological closing (fill small holes in the foreground)
    cv::dilate(*imgThresholded, *imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, *thresholdedSize));
    cv::erode(*imgThresholded, *imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, *thresholdedSize));
    cout << "\n\nLowHSV: " << LowHSV << " HighHSV: " << HightHSV << endl;
    // imgThresholded caght black adn white
    string detected_black_pixels = detect_black_pixels(imgThresholded) ? "TRUE" : "FALSE";
    string detected_white_pixels = detect_white_pixels(imgThresholded) ? "TRUE" : "FALSE";
    cout << "HasBlack[" << detected_black_pixels << "]" << endl;
    cout << "HasWhite[" << detected_white_pixels << "]" << endl;
}

void ColorDetection::color_detection_on_video() {
    cv::Size thresholdedSize = cv::Size(1, 1);
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
        cout << "Cannot open the web cam" << endl;

    cv::namedWindow("Control", cv::WINDOW_AUTOSIZE);

    int iLowH = 0;
    int iHighH = 179;

    int iLowS = 0;
    int iHighS = 255;

    int iLowV = 46;
    int iHighV = 255;

    // Create trackbars in "Control" window
    cv::createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cv::createTrackbar("HighH", "Control", &iHighH, 179);

    cv::createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cv::createTrackbar("HighS", "Control", &iHighS, 255);

    cv::createTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cv::createTrackbar("HighV", "Control", &iHighV, 255);

    while (cv::waitKey(30) != 'q')
    {
        cv::Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal);

        if (!bSuccess)
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        crop_black_borders(&imgOriginal);

        cv::Mat imgHSV;

        cv::cvtColor(imgOriginal, imgHSV, cv::COLOR_BGR2HSV); // Convert the captured frame from BGR to HSV

        cv::Mat imgThresholded;

        cv::Scalar LowHSV = cv::Scalar(iLowH, iLowS, iLowV);
        cv::Scalar HightHSV = cv::Scalar(iHighH, iHighS, iHighV);

        cv::inRange(imgHSV, LowHSV, HightHSV, imgThresholded); // Threshold the image

        // morphological opening (remove small objects from the foreground)
        cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, thresholdedSize));
        cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, thresholdedSize));

        // morphological closing (fill small holes in the foreground)
        cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, thresholdedSize));
        cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, thresholdedSize));

        cout << "\n\nLowHSV: " << LowHSV << " HighHSV: " << HightHSV << endl;

        // imgThresholded caght black
        string detected_black_pixels = detect_black_pixels(&imgThresholded) ? "TRUE" : "FALSE";
        cout << "HasBlack[" << detected_black_pixels << "]" << endl;

        cv::imshow("Original", imgOriginal);
        cv::imshow("HSV", imgHSV);
        cv::imshow("Thresholded Image", imgThresholded);
    }
}

void ColorDetection::crop_black_borders(cv::Mat* image) {
    cv::Mat gray;
    cv::Mat thresh;
    vector<vector<cv::Point>> contours;
    cv::Rect rect;
    cv::cvtColor(*image, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, thresh, 1, 255, cv::THRESH_BINARY);
    cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    vector<cv::Point> cnt = contours[0];
    rect = cv::boundingRect(cnt);
    *image = (*image)(rect);
}

bool ColorDetection::detect_black_pixels(cv::Mat* image) {
    int TotalNumberOfPixels = image->rows * image->cols;
    int ZeroPixels = TotalNumberOfPixels - cv::countNonZero(*image);
    return ZeroPixels > 0;
}

bool ColorDetection::detect_white_pixels(cv::Mat* image) {
    return cv::countNonZero(*image) > 0;
}