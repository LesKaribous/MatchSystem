#include "lidar.h"
#include <core/common/ydlidar_def.h>
#include <iostream>
#include <mutex>
#include <thread>

namespace Lidar {
    Lidar::Lidar(const std::string &port){
        ydlidar::os_init();

        laser.setlidaropt(LidarPropSerialPort, port.c_str(), port.size());

        laser.setlidaropt(LidarPropSerialBaudrate, &Property::baud_rate, sizeof(int));
        laser.setlidaropt(LidarPropDeviceType, &Property::connection, sizeof(int));
        laser.setlidaropt(LidarPropSampleRate, &Property::sample_rate, sizeof(int));
        laser.setlidaropt(LidarPropLidarType, &Property::type, sizeof(int));
        laser.setlidaropt(LidarPropAbnormalCheckCount, &Property::abnormal_count, sizeof(int));

        laser.setlidaropt(LidarPropFixedResolution, &Property::fixed_resolution, sizeof(bool));
        laser.setlidaropt(LidarPropReversion, &Property::reversion, sizeof(bool));
        laser.setlidaropt(LidarPropInverted, &Property::clockwise, sizeof(bool));
        laser.setlidaropt(LidarPropAutoReconnect, &Property::auto_reconnect, sizeof(bool));
        laser.setlidaropt(LidarPropSingleChannel, &Property::single_channel, sizeof(bool));
        laser.setlidaropt(LidarPropIntenstiy, &Property::intensity, sizeof(bool));
        laser.setlidaropt(LidarPropSupportMotorDtrCtrl, &Property::dtr_ctrl, sizeof(bool));

        laser.setlidaropt(LidarPropMaxAngle, &Property::max_angle, sizeof(float));
        laser.setlidaropt(LidarPropMinAngle, &Property::min_angle, sizeof(float));
        laser.setlidaropt(LidarPropMaxRange, &Property::max_range, sizeof(float));
        laser.setlidaropt(LidarPropMinRange, &Property::min_range, sizeof(float));
        laser.setlidaropt(LidarPropScanFrequency, &Property::scan_frequency, sizeof(float));
    }

    bool Lidar::init(){
        connected = laser.initialize();

        if(connected){
            std::cout << "Lidar Initialized" << std::endl;
            return laser.turnOn();
        }
        
        std::cout << laser.DescribeError() << std::endl;
        return false;
    }

    void Lidar::run(){
        std::thread scanning_thread(&Lidar::run_impl, this);
    }

    void Lidar::run_impl(){
        const std::lock_guard<std::mutex> lock(scan_mutex);

        while (connected && ydlidar::os_isOk()) {
            if (laser.doProcessSimple(scan)) {  
                std::cout << "Scan received " << scan.stamp << " : " << (unsigned int)scan.points.size() << "ranges is " <<  1.0 / scan.config.scan_time << " Hz" << std::endl;
            } else {
                std::cerr << "Failed to get Lidar Data" << std::endl;
            }
        }
    }

    void Lidar::stop(){
        laser.turnOff();
        connected = false;

        scanning_thread.join();

        std::cout << "Lidar stopped" << std::endl;
    }


    const LaserScan &Lidar::getScan() {
        const std::lock_guard<std::mutex> lock(scan_mutex);
        
        return scan;
    }
}