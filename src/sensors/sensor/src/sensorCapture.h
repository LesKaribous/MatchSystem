#pragma once

#include <string>
#include <fstream>

namespace Sensor{
    struct SensorCapture{
        SensorCapture() : save_counter(0) {};
        SensorCapture(const std::string &folder, const std::string &prefix);

        inline void setPath(const std::string &path){_path = path;}
        inline void setFolder(const std::string &folder){_folder = folder;}
        inline void setPrefix(const std::string &prefix) {_prefix = prefix;}
        inline void setExtension(const std::string &extension) {_extension = extension;}
        inline const std::string &getPath() const {return _path;}

        virtual void initFile();
        void closeFile();
        
        virtual void saveData() = 0;

        protected:
            unsigned long save_counter;
            std::string _path;
            std::string _folder;
            std::string _prefix;
            std::string _extension;

            std::ofstream file;
    };
}