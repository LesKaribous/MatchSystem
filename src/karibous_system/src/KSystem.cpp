#include "KSystem.h"
#include "camera.h"
#include "camera_calib.h"
#include "lidar.h"
#include <cstring>
#include <memory>
#include <string>
#include <utility>

#include "Logger.h"

void KSystem::loadConfig(const std::string &path){
    config.load(path);
    
    for(const auto& c : config.getList()){
        if(!std::strcmp(c.at<std::string>("type").c_str(), "Lidar")){
            lidars.insert(std::make_pair(c.at<std::string>("name"), std::make_shared<Sensor::Lidar>(c)));

            Logger::Logger::getInstance().logInfo(c.toString());
        }

        if(!std::strcmp(c.at<std::string>("type").c_str(), "Camera")){
            cameras.insert(std::make_pair(c.at<std::string>("name"), std::make_shared<Sensor::Camera>(c)));

            Logger::Logger::getInstance().logInfo(c.toString());
        }
    }
}


void KSystem::init(){
    for(auto &l : lidars){
        if(!l.second->init()){
            Logger::Logger::getInstance().logError("Failed to init Lidar : " + l.first);
        }
        
    }

    // for (auto &c: cameras) {
    //     c.second->init();
    // }

    Logger::Logger::getInstance().logInfo("[KSystem] Initialized");
}

bool KSystem::runSensor(const std::string &name){
    if(lidars.count(name)){
        lidars.at(name)->run();
        Logger::Logger::getInstance().logInfo("[KSystem] Run Lidar : " + name);
        return true;
    }
    else if(cameras.count(name)){
        cameras.at(name)->run();
        Logger::Logger::getInstance().logInfo("[KSystem] Run Camera : " + name);
        return true;
    }
    
    return false;
}

void KSystem::runSensors(){
    for(auto &l : lidars){
        Logger::Logger::getInstance().logInfo("[KSystem] Run Lidar : " + l.second->getProperties().name);
        l.second->run();
    }

    for (auto &c: cameras) {
        Logger::Logger::getInstance().logInfo("[KSystem] Run Camera : " + c.second->getProperties().name);
        c.second->run();
    }
}

void KSystem::stopSensor(const std::string &name){
    if(lidars.count(name)){
        lidars.at(name)->stop();
        Logger::Logger::getInstance().logInfo("[KSystem] Stop Lidar : " + name);
    }
    else if(cameras.count(name)){
        cameras.at(name)->stop();
        Logger::Logger::getInstance().logInfo("[KSystem] Stop Camera : " + name);
    }
}

void KSystem::stopSensors(){
    for(auto &l : lidars){
        Logger::Logger::getInstance().logInfo("[KSystem] Stop Lidar : " + l.second->getProperties().name);
        l.second->stop();
    }

    for (auto &c: cameras) {
        Logger::Logger::getInstance().logInfo("[KSystem] Stop Camera : " + c.second->getProperties().name);
        c.second->stop();
    }
}

void KSystem::saveData(){
    for(auto &l : lidars){
        l.second->saveData();
    }

    for (auto &c: cameras) {
        c.second->saveData();
    }
}

void KSystem::calibrateCamera(const std::string &name){
    Sensor::CameraCalib calibration(cameras.at(name));

    calibration.start(cv::Size(10, 7));
}

