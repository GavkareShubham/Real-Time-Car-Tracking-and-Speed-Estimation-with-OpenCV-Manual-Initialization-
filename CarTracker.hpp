#ifndef CAR_TRACKER_HPP
#define CAR_TRACKER_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <vector>

class CarTracker {
public:
    CarTracker(double conversionFactor, int fps);
    void selectInitialCars(cv::Mat& frame);
    void trackCars(cv::Mat& frame);
    void displayTracking(cv::Mat& frame);

private:
    double conversionFactor_;
    int fps_;
    std::vector<cv::Ptr<cv::Tracker>> trackers_;
    std::vector<cv::Rect> objects_;
    std::vector<cv::Rect> prevPositions_;
};

#endif // CAR_TRACKER_HPP
