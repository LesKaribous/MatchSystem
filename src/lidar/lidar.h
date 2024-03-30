#pragma once

#include "CYdLidar.h"
#include <atomic>
#include <core/common/ydlidar_datatype.h>
#include <core/common/ydlidar_def.h>
#include <iostream>
#include <mutex>
#include <string>
#include <algorithm>
#include <cctype>
#include <thread>
#if defined(_MSC_VER)
#pragma comment(lib, "ydlidar_sdk.lib")
#endif

namespace  Lidar{
    struct Property{
        const static int baud_rate = 512000;
        const static int type = TYPE_TOF;
        const static int connection = YDLIDAR_TYPE_SERIAL;
        const static int sample_rate = 20;
        const static int abnormal_count = 4;

        const static bool fixed_resolution = false;
        const static bool reversion = false;
        const static bool clockwise = false;
        const static bool auto_reconnect = true;
        const static bool single_channel = false;
        const static bool intensity = false;
        const static bool dtr_ctrl = false;

        static constexpr float max_angle = 180.0f;     // unit : deg
        static constexpr float min_angle = -180.0f;    // unit : deg
        static constexpr float max_range = 12.f;       // unit : m
        static constexpr float min_range = 0.05f;      // unit : m
        static constexpr float scan_frequency = 10.f;  // unit : Hz
    };

    struct Lidar{
        Lidar(const std::string &port);
        ~Lidar() = default;

        bool init();
        void run();
        void stop();

        inline bool isConnected() {return connected;}
        const LaserScan& getScan();

        private:
            CYdLidar laser;

            std::atomic<bool> connected;

            LaserScan scan;
            std::mutex scan_mutex;

            std::thread scanning_thread;

            void run_impl();
    };
}