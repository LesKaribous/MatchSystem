#include <cstdlib>
#include <iostream>
#include "karibous_system/src/KSystem.h"
#include "logger/src/Logger.h"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static bool run = true;

void signalHandler(int signal) {
    std::cout << "Ctrl+C pressed, exiting..." << std::endl;
    run = false;
}

int main(int argc, char *argv[]) {
    std::cout << "Welcone to the main computation" << std::endl;
    

    KSystem ksystem;
    signal(SIGINT, signalHandler);

    ksystem.loadConfig("/home/tduvinage/Documents/CDR2024/KaribousBrainSystem/etc/KabirousSystem.yaml");
    
    ksystem.lidar("lidar").setPath("/home/tduvinage/Documents/CDR2024/KaribousBrainSystem/output/lidar.csv");

    ksystem.init();

    // ksystem.runSensor("camera");
    ksystem.runSensor("lidar");

    //ksystem.calibrateCamera("camera");

    // ksystem.camera("camera").setFolder("/home/tduvinage/Documents/CDR2024/KaribousBrainSystem/output/images/");
    // ksystem.camera("camera").setPrefix("test_");

    while (run) {
        ksystem.saveData();
    }

    ksystem.stopSensor("lidar");

    Logger::Logger::getInstance().logInfo("fin du programme");
    return EXIT_SUCCESS;
}

