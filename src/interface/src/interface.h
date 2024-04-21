#pragma once

#include "KSystem.h"
#include <thread>

namespace Interface {
    struct KaribousApp{
        KaribousApp() = default;
        ~KaribousApp() = default;

        void init();

        void run();

        private:
            std::unique_ptr<KSystem> system;

            std::thread app_thread;

            void run_impl();
    };

}