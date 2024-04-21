#pragma once

#include "configuration.h"
#include "sensor.h"
#include <mutex>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <string>

#include <opencv4/opencv2/opencv.hpp>

namespace Sensor{
    struct Camera : public Sensor{
        private:
            void run_impl() override;

            struct Property{
                std::string name;
                int index;
                int frame_width;
                int frame_height;
                bool save_data;
                unsigned frequency;
            } properties;

            cv::VideoCapture cam;
            cv::Mat frame;
            std::mutex frame_mutex;

        public:
            Camera() = default;
            ~Camera();

            Camera(int index);
            Camera(const Configuration::ConfigurationAttribute &config);

            inline void setIndex(int index){properties.index = index;}

            bool init() override;
            void stop() override;
            void saveData() override;

    
            void loadConfig(const Configuration::ConfigurationAttribute &config) override;
            inline Property& getProperties() {return properties;}
            void setProperties(const Property &pros);

            cv::Mat getFrame();

    };
}