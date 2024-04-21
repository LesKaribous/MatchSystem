#include "sensor.h"


namespace Sensor {
    void Sensor::run(){
        run_thread = std::thread(&Sensor::run_impl, this);
    }
}