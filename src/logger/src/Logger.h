#pragma once

#include <iostream>
#include <string>
#include <mutex>

namespace Logger {
    struct Logger {
        public:
            static Logger& getInstance() {
                static Logger instance; // Guaranteed to be destroyed, instantiated on first use
                return instance;
            }

            void logWarning(const std::string& message);
            void logInfo(const std::string& message);
            void logError(const std::string& message);
            void log(const std::string& message);

        private:
            Logger() {} // Private constructor to prevent instantiation
            Logger(const Logger&) = delete; // Delete copy constructor
            Logger& operator=(const Logger&) = delete; // Delete copy assignment operator
            std::mutex mutex_;
    };
}