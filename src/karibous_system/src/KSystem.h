#pragma once

#include "configuration.h"
#include "lidar.h"
#include "camera.h"
#include "camera_calib.h"

#include <map>
#include <memory>
#include <string>

struct KSystem{
    KSystem() = default;
    ~KSystem() = default;

    void loadConfig(const std::string &config);

    void init();

    inline Sensor::Lidar& lidar(const std::string &name){return *lidars.at(name);}
    inline Sensor::Camera& camera(const std::string &name){return *cameras.at(name);}

    void runSensors();
    bool runSensor(const std::string &name);

    void stopSensor(const std::string &name);
    void stopSensors();

    void calibrateCamera(const std::string &name);

    void saveData();

    private:
        Configuration::Configuration config;

        std::map<std::string, std::shared_ptr<Sensor::Lidar>> lidars;
        std::map<std::string, std::shared_ptr<Sensor::Camera>> cameras;
};