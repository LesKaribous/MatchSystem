#pragma once

#include <CYdLidar.h>

#include <atomic>
#include <core/common/ydlidar_datatype.h>
#include <core/common/ydlidar_def.h>
#include <iostream>
#include <mutex>
#include <string>
#include <algorithm>
#include <cctype>
#include <thread>

#include "configuration.h"
#include "Logger.h"

#include "sensor.h" // FIX BUG

namespace  Sensor{
    struct Lidar : public Sensor{
        private:
            CYdLidar laser;

            struct Property{
                std::string name;
                std::string port;
                int baud_rate = 512000;
                int mode = TYPE_TOF;
                int connection = YDLIDAR_TYPE_SERIAL;
                int sample_rate = 20;
                int abnormal_count = 4;        
                bool fixed_resolution = false;
                bool reversion = false;
                bool clockwise = false;
                bool auto_reconnect = true;
                bool single_channel = false;
                bool intensity = false;
                bool dtr_ctrl = false;        float max_angle = 180.0f;     // unit : deg
                float min_angle = -180.0f;    // unit : deg
                float max_range = 12.f;       // unit : m
                float min_range = 0.05f;      // unit : m
                float scan_frequency = 10.f;  // unit : Hz
                int optval = 8;
                bool save_data = false;
            } properties;

            LaserScan scan;
            std::mutex scan_mutex;

            void run_impl() override;

        public:
            Lidar();
            Lidar(const Configuration::ConfigurationAttribute &config);
            Lidar(const std::string &port);
            ~Lidar();

            bool init() override;
            void stop() override;
            //void run() override;
            void saveData() override;
    
            void loadConfig(const Configuration::ConfigurationAttribute &config) override;

            inline  Property& getProperties() {return properties;}
            const LaserScan& getScan();
    };
}