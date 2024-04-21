#include "interface.h"

namespace Interface {
    void KaribousApp::init(){

    }

    void KaribousApp::run(){
        app_thread = std::thread(&KaribousApp::run_impl, this);
    }

    void KaribousApp::run_impl(){
        while(true){
               
        }
    }   
}