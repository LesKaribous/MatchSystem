#include "camera.h"
#include "Logger.h"
#include "configuration.h"
#include "sensor.h"
#include <chrono>
#include <mutex>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/persistence.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <stdexcept>
#include <string>

namespace Sensor {
    Camera::Camera(int index){
        properties.index = index;
    }

    Camera::Camera(const Configuration::ConfigurationAttribute &config){
        loadConfig(config);
    }

    Camera::~Camera(){
        //stop();

        //cv::destroyAllWindows();
    }

    void Camera::loadConfig(const Configuration::ConfigurationAttribute &config){
        properties.name = config.at<std::string>("name");
        properties.index = config.at<int>("index");
        properties.frame_height = config.at<int>("frame_height");
        properties.frame_width = config.at<int>("frame_width");
        properties.save_data = config.at<bool>("save_data");
        properties.frequency = config.at<unsigned>("frequency");
    }

    void Camera::run_impl(){
        while(connected){            
            frame_mutex.lock();
            if(cam.read(frame)){
                state = RUNNING;
                frame_mutex.unlock();

                //TODO consider the tume to capture the frame
                cv::waitKey(1000 / properties.frequency);

                // cv::imshow(properties.name, frame);
                
                // if ( (char)27 == (char) cv::waitKey(1) ) {
                //     cv::destroyWindow(properties.name);
                // }
                
            }
            else {
                state = STOPPED;
                Logger::Logger::getInstance().logError("[Camera] frame dropped");
            
            }

            
        }
    }

    bool Camera::init(){
        if(cam.open(properties.index)){
            cam.set(cv::CAP_PROP_FRAME_WIDTH,properties.frame_width);
            cam.set(cv::CAP_PROP_FRAME_HEIGHT,properties.frame_height); 

            connected = true;

            Logger::Logger::getInstance().logInfo("[Camera] Camera : " + properties.name + " is connected");
            return true;
        }

        Logger::Logger::getInstance().logError("[Camera] Cannot connect to camera index : " + std::to_string(properties.index));
        return false;
    }

    void Camera::stop(){
        //cv::destroyWindow(properties.name);
        
        if(cam.isOpened()){
            cam.release();
            connected = false;
        }

        if(run_thread.joinable())
            run_thread.join();

        Logger::Logger::getInstance().logInfo("[Camera] Stop camera : " + properties.name);
    }

    void Camera::saveData(){
        if(properties.save_data && state == RUNNING){
            Logger::Logger::getInstance().logInfo("[Camera] saving data");
            const auto current_time = std::chrono::system_clock::now();

            cv::imwrite(_path + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(current_time.time_since_epoch()).count()) + "_" + _prefix + std::to_string(save_counter) + ".png", getFrame());
            save_counter++;

        }
    }

    cv::Mat Camera::getFrame() {
        const std::lock_guard<std::mutex> guard(frame_mutex);
        return frame.clone();
    }

    void Camera::setProperties(const Property &props){
        properties.name = props.name;
        properties.index = props.index;
        properties.frame_height = props.frame_height;
        properties.frame_width = props.frame_width;
    }

}