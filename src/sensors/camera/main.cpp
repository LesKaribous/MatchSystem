#include <cstdlib>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include <iostream>
#include <string>
 
using namespace std;
using namespace cv;

int cameraIndex = 0;

int main(int argc, char *argv[])
{

  if(argc > 1){
    cameraIndex = atoi(argv[1]);
  }
 
  // Create a VideoCapture object and use camera to capture the video
  VideoCapture cap(cameraIndex); 
  cap.set(CAP_PROP_FRAME_WIDTH,1920);
  cap.set(CAP_PROP_FRAME_HEIGHT,1080); 

  cv::waitKey(1000);
 
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream" << endl;
        return -1;
  }

  while(1){
 
    Mat frame;
    
    // Capture frame-by-frame
    cap >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    Size patternsize(10,7); //interior number of corners
    Mat gray;
    cvtColor(frame,gray,COLOR_BGR2GRAY);//source image
    vector<Point2f> corners; //this will be filled by the detected corners

    //CALIB_CB_FAST_CHECK saves a lot of time on images
    //that do not contain any chessboard corners
    bool patternfound = findChessboardCorners(gray, patternsize, corners,
                        cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE | cv::CALIB_CB_FAST_CHECK);

    if(patternfound)
      cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::EPS  + TermCriteria::MAX_ITER, 30, 0.1));

    drawChessboardCorners(frame, patternsize, Mat(corners), patternfound);

    // Display the resulting frame    
    imshow( "Frame", frame );
  
    // Press  ESC on keyboard to  exit
    char c = (char)waitKey(1);
    if( c == 27 ) 
      break;
  }
 
  // When everything done, release the video capture and write object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
  return 0;
}