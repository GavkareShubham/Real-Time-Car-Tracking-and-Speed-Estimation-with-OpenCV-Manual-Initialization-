#include "CarTracker.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    cv::VideoCapture cap("Cars.mp4");
    if (!cap.isOpened())
    {
        std::cerr << "Error opening video stream" << std::endl;
        return -1;
    }

    double conversionFactor = 0.05; // Example conversion factor (pixels to meters)
    int fps = static_cast<int>(cap.get(cv::CAP_PROP_FPS));

    CarTracker carTracker(conversionFactor, fps);

    cv::Mat frame;
    cap.read(frame);
    carTracker.selectInitialCars(frame);

    while (cap.read(frame))
    {
        carTracker.trackCars(frame);
        carTracker.displayTracking(frame);
        if (cv::waitKey(30) >= 0)
            break;
    }

    return 0;
}
