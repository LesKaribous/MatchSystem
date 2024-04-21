#include "camera_calib.h"
#include "Logger.h"
#include "camera.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

namespace Sensor {
        CameraCalib::CameraCalib(std::shared_ptr<Camera> camera){
            cam = camera;
            capture = false;
        }

        void CameraCalib::start(const cv::Size &patternSize, int valid){
            cv::Mat gray;

            while(shots.size() < valid){
                if(cam->getState() == Camera::RUNNING){   
                    cv::imshow("calibration", cam->getFrame());

                    cv::setMouseCallback("calibration", mouseCallbackCallibration, this);

                    if(capture){
                        cv::Mat frame;
                        cvtColor(cam->getFrame(), frame, cv::COLOR_BGR2GRAY);

                        std::vector<cv::Point2f> corners;

                        bool patternfound = findChessboardCorners(gray, patternSize, corners,
                                cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE | cv::CALIB_CB_FAST_CHECK);

                        if(patternfound){
                            cv::cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS  + cv::TermCriteria::MAX_ITER, 30, 0.1));
                            cv::drawChessboardCorners(frame, patternSize, cv::Mat(corners), patternfound);

                            // Display the resulting frame    
                            cv::imshow( "Frame", frame );

                            shots.push_back(cam->getFrame());
                            
                            std::cout << "element added to the list" << std::endl;
                        }

                    }

                    cv::cvtColor(cam->getFrame(), gray,cv::COLOR_BGR2GRAY);
                }
            
            }
        }

        void CameraCalib::mouseCallbackCallibration(int event, int x, int y, int, void* calibration){
            CameraCalib* calib = reinterpret_cast<CameraCalib*>(calibration);
            
            if(event == cv::EVENT_LBUTTONDOWN){
                calib->capture = false;
            }
        }
}