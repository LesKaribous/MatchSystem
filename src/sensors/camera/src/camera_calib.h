#pragma once

#include "camera.h"
#include <atomic>
#include <memory>
#include <opencv2/highgui.hpp>
#include <vector>

namespace Sensor {
    struct CameraCalib{
        public:
            CameraCalib(std::shared_ptr<Camera> camera);
            ~CameraCalib() = default;

            void start(const cv::Size &patternSize, int valid = 6);

        private:
            std::shared_ptr<Camera> cam;
            static void mouseCallbackCallibration(int event, int x, int y, int, void* calibration);

            std::vector<cv::Mat> shots;

            bool capture;
    };

}