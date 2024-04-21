#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <iostream>

#include <yaml-cpp/emitter.h>
#include <yaml-cpp/yaml.h>

namespace Configuration {
    struct ConfigurationAttribute{
        private:
            YAML::Node _node;

        public:
            ConfigurationAttribute(const YAML::Node &node){
                _node = node;
            }

            inline const ConfigurationAttribute &get() const {return *this;}
            inline const YAML::Node &getNode() const {return _node;}
            
            template<typename T>
            const T at(const std::string &index) const{return _node[index].as<T>();}

            inline const std::string toString() const{
                YAML::Emitter emitter;
                emitter << _node;
                return std::string(emitter.c_str()) + "\n";
            }
    };

    struct Configuration{
        Configuration() = default;
        Configuration(const std::string &path);

        inline Configuration &getConfig() {return *this;}

        inline std::vector<ConfigurationAttribute> &getList() {return config;};

        bool load(const std::string &path);

        private:
            std::vector<ConfigurationAttribute> config;

    };
}

