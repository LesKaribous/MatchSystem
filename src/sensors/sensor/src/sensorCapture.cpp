#include "sensorCapture.h"
#include "Logger.h"

namespace Sensor {
    SensorCapture::SensorCapture(const std::string &folder, const std::string &prefix): _folder(folder), _prefix(prefix), save_counter(0) {}

    void SensorCapture::initFile(){
        if(_path.empty())
            file.open(_folder + _prefix + _extension);
        else
            file.open(_path);

        Logger::Logger::getInstance().logInfo("[SensorCapture] file open : " + _path);
    }

    void SensorCapture::closeFile(){
        if(file.is_open()) 
            file.close();
    }
}