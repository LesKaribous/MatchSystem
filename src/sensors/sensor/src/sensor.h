#pragma once

#include "sensorCapture.h"

#include "configuration.h"
#include <atomic>
#include <thread>


namespace Sensor {
    struct Sensor : public SensorCapture{
        Sensor() : connected(false), state(STOPPED) {};
        ~Sensor() = default;
        
        enum State{
            RUNNING,
            STOPPED
        };

        virtual void loadConfig(const Configuration::ConfigurationAttribute &config) = 0;
        virtual bool init() = 0;
        virtual void stop() = 0;
        virtual void run();

        inline bool isConnected() {return connected;}
        inline const State getState() {return state;}

        protected:
            virtual void run_impl() = 0;

            std::atomic<bool> connected;
            std::thread run_thread;

            std::atomic<State> state;
    };
}