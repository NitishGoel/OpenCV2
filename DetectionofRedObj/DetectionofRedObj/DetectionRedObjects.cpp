#include <iostream>

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\opencv.hpp"

//This function threshold the HSV image and create a binary image
IplImage* GetThresholdedImage(IplImage* imgHSV){        
       IplImage* imgThresh=cvCreateImage(cvGetSize(imgHSV),IPL_DEPTH_8U, 1);
       cvInRangeS(imgHSV, cvScalar(170,160,60), cvScalar(180,256,256), imgThresh); //range of red color
       return imgThresh;
} 
 
int main(){
      CvCapture* capture =0;       

      capture = cvCaptureFromCAM(0);
      if(!capture){
            printf("Capture failure\n");
            return -1;
      }
      
      IplImage* frame=0;

      cvNamedWindow("Video");      
      cvNamedWindow("Thresholding");


      //iterate through each frames of the video      
      while(true){

            frame = cvQueryFrame(capture);            
            if(!frame) break;

            frame=cvCloneImage(frame); 

            IplImage* imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3); 
            cvCvtColor(frame, imgHSV, CV_BGR2HSV); //Change the color format from BGR to HSV
            IplImage* imgThresh = GetThresholdedImage(imgHSV);
          
            
            cvShowImage("Thresholding", imgThresh);            
            cvShowImage("Video", frame);
            
            cvReleaseImage(&imgHSV);
            cvReleaseImage(&imgThresh);            
            cvReleaseImage(&frame);

       
            int c = cvWaitKey(10);
            if((char)c==27 ) break;      
      }

      cvDestroyAllWindows() ;
      cvReleaseCapture(&capture);     

      return 0;
}