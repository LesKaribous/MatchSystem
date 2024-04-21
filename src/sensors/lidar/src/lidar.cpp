#include "lidar.h"
#include "Logger.h"
#include <chrono>
#include <core/common/ydlidar_datatype.h>
#include <core/common/ydlidar_def.h>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <mutex>
#include <ostream>
#include <string>
#include <thread>

namespace Sensor {
    Lidar::Lidar(){
        properties.port = "";
    }

    Lidar::Lidar(const std::string &port){
        properties.port = port;
    }

    Lidar::Lidar(const Configuration::ConfigurationAttribute &config){
        loadConfig(config);
    }

    Lidar::~Lidar(){
        //stop();
    }

    bool Lidar::init(){
        initFile();

        ydlidar::os_init();

        std::map<std::string, std::string> ports = ydlidar::lidarPortList();

        Logger::Logger::getInstance().logInfo("[Lidar] Ports list");
        if(!ports.empty()) {
            for(auto c : ports){
                Logger::Logger::getInstance().logInfo(c.second);
            }
        }

        if(!properties.port.empty())
        {
            laser.setlidaropt(LidarPropSerialPort, properties.port.c_str(), properties.port.size());

            laser.setlidaropt(LidarPropSerialBaudrate, &properties.baud_rate, sizeof(int));
            laser.setlidaropt(LidarPropDeviceType, &properties.connection, sizeof(int));
            laser.setlidaropt(LidarPropSampleRate, &properties.sample_rate, sizeof(int));
            laser.setlidaropt(LidarPropLidarType, &properties.mode, sizeof(int));
            laser.setlidaropt(LidarPropAbnormalCheckCount, &properties.abnormal_count, sizeof(int));

            laser.setlidaropt(LidarPropFixedResolution, &properties.fixed_resolution, sizeof(bool));
            laser.setlidaropt(LidarPropReversion, &properties.reversion, sizeof(bool));
            laser.setlidaropt(LidarPropInverted, &properties.clockwise, sizeof(bool));
            laser.setlidaropt(LidarPropAutoReconnect, &properties.auto_reconnect, sizeof(bool));
            laser.setlidaropt(LidarPropSingleChannel, &properties.single_channel, sizeof(bool));
            laser.setlidaropt(LidarPropIntenstiy, &properties.intensity, sizeof(bool));
            laser.setlidaropt(LidarPropSupportMotorDtrCtrl, &properties.dtr_ctrl, sizeof(bool));

            laser.setlidaropt(LidarPropMaxAngle, &properties.max_angle, sizeof(float));
            laser.setlidaropt(LidarPropMinAngle, &properties.min_angle, sizeof(float));
            laser.setlidaropt(LidarPropMaxRange, &properties.max_range, sizeof(float));
            laser.setlidaropt(LidarPropMinRange, &properties.min_range, sizeof(float));
            laser.setlidaropt(LidarPropScanFrequency, &properties.scan_frequency, sizeof(float));

            laser.setlidaropt(LidarPropIntenstiyBit, &properties.optval, sizeof(int));

            laser.enableGlassNoise(false);
            laser.enableSunNoise(false);

            laser.setEnableDebug(false);

            connected = laser.initialize();

            if(connected && ydlidar::os_isOk()){
                Logger::Logger::getInstance().logInfo("[Lidar] Initialized");
                return laser.turnOn();
            }
            
            Logger::Logger::getInstance().logError("[Lidar]" + std::string(laser.DescribeError()));
            return false;
        }

        Logger::Logger::getInstance().logError("[Lidar] Please set port" );
        return false;
    }

    void Lidar::run_impl(){
        while (connected && ydlidar::os_isOk()) {
            scan_mutex.lock();
            if (!laser.doProcessSimple(scan)) {  
                Logger::Logger::getInstance().logError("[Lidar] Failed to get Lidar Data");
            }

            scan_mutex.unlock();

            usleep(1000000/properties.scan_frequency);
        }
    }

    void Lidar::stop(){
        laser.turnOff();
        laser.disconnecting();
        connected = false;

        closeFile();

        if(run_thread.joinable())
            run_thread.join();
    }

    void Lidar::saveData(){
        if(file.is_open()){
            LaserScan scan_points = getScan();
            const auto current_time = std::chrono::system_clock::now();

            for(size_t i = 0; i < scan_points.points.size(); i++){
                const LaserPoint &p = scan_points.points.at(i);
                file << std::chrono::duration_cast<std::chrono::microseconds>(current_time.time_since_epoch()).count() << ";" << i << ";" << p.angle * 180 / M_PI << ";" << p.range << ";" << p.intensity << "\n";
            }
        }
        else{
            Logger::Logger::getInstance().logInfo("[Lidar] Cannot save data");
        }
    }


    const LaserScan &Lidar::getScan() {
        const std::lock_guard<std::mutex> lock(scan_mutex);
        return scan;
    }

    void Lidar::loadConfig(const Configuration::ConfigurationAttribute &config){
        properties.baud_rate = config.at<int>("baud_rate");

        if(!std::strcmp(config.at<std::string>("mode").c_str(), "TOF"))
            properties.mode = TYPE_TOF;
        else if(!std::strcmp(config.at<std::string>("mode").c_str(), "TRIANGLE"))
            properties.mode = TYPE_TRIANGLE;

        if(!std::strcmp(config.at<std::string>("connection").c_str(), "Serial"))
            properties.connection = YDLIDAR_TYPE_SERIAL;
        
        properties.port = config.at<std::string>("port");
        properties.name = config.at<std::string>("name");
        properties.sample_rate = config.at<int>("sample_rate");
        properties.abnormal_count = config.at<int>("abnormal_count");
        properties.fixed_resolution = config.at<bool>("fixed_resolution");
        properties.reversion = config.at<bool>("reversion");
        properties.clockwise = config.at<bool>("clockwise");
        properties.auto_reconnect = config.at<bool>("auto_reconnect");
        properties.single_channel = config.at<bool>("single_channel");
        properties.intensity = config.at<bool>("intensity");
        properties.dtr_ctrl = config.at<bool>("dtr_ctrl");
        properties.max_angle = config.at<float>("max_angle");
        properties.min_angle = config.at<float>("min_angle");
        properties.max_range = config.at<float>("max_range");
        properties.min_range = config.at<float>("min_range");
        properties.scan_frequency = config.at<float>("scan_frequency");
        properties.optval = config.at<float>("optval");

        properties.save_data = config.at<bool>("save_data");
    }   
}