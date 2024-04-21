#include "configuration.h"
#include <ostream>
#include <type_traits>
#include <yaml-cpp/emitter.h>

#include "Logger.h"


namespace Configuration {
    Configuration::Configuration(const std::string &path){
        load(path);
    }


    bool Configuration::load(const std::string &path){
        try {

            YAML::Node doc = YAML::LoadFile(path);

            for(unsigned i=0;i<doc.size();i++) {
                config.push_back(ConfigurationAttribute(doc[i]));
            }

            return true;
            
        } catch (YAML::ParserException &e) {
            Logger::Logger::getInstance().logError(e.what());
            return false;
        }
    }   
}

