#include "CarTracker.hpp"
#include <cmath>
#include <iostream>

CarTracker::CarTracker(double conversionFactor, int fps)
    : conversionFactor_(conversionFactor), fps_(fps) {}

void CarTracker::selectInitialCars(cv::Mat &frame)
{
    std::vector<cv::Rect> initialBoxes;
    cv::selectROIs("Select Cars", frame, initialBoxes, false);

    for (const auto &box : initialBoxes)
    {
        cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();
        tracker->init(frame, box);
        trackers_.push_back(tracker);
        objects_.push_back(box);
    }
}

void CarTracker::trackCars(cv::Mat &frame)
{
    for (size_t i = 0; i < trackers_.size(); ++i)
    {
        trackers_[i]->update(frame, objects_[i]);
    }
}

void CarTracker::displayTracking(cv::Mat &frame)
{
    for (size_t i = 0; i < objects_.size(); ++i)
    {
        const auto &object = objects_[i];
        if (prevPositions_.size() > i)
        {
            const auto &prevPosition = prevPositions_[i];
            double distance = cv::norm(object.tl() - prevPosition.tl());
            double distanceMeters = distance * conversionFactor_;
            double speedMps = distanceMeters * fps_;
            double speedKmh = speedMps * 3.6;

            cv::putText(frame, "Speed: " + std::to_string(speedKmh) + " km/h",
                        object.tl(), cv::FONT_HERSHEY_SIMPLEX, 0.75,
                        cv::Scalar(0, 255, 0), 2);
        }
    }

    prevPositions_ = objects_;

    for (const auto &object : objects_)
    {
        cv::rectangle(frame, object, cv::Scalar(255, 0, 0), 2, 1);
    }

    cv::imshow("Car Tracking and Speed Estimation", frame);
}
