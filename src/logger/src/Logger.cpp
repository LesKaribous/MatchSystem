#include "Logger.h"

namespace Logger {
    void Logger::logWarning(const std::string& message) {
        log("\033[1;33m[WARNING] \033[0m" + message);
    }

    void Logger::logInfo(const std::string& message) {
        log("\033[1;36m[INFO] \033[0m" + message);
    }

    void Logger::logError(const std::string& message) {
        log("\033[1;31m[ERROR] \033[0m" + message);
    }

    void Logger::log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << message << std::endl;
    }
}