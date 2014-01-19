#include <iostream>

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\opencv.hpp"

IplImage* imgTracking;
int lastX = -1;
int lastY = -1;

//This function threshold the HSV image and create a binary image
IplImage* GetThresholdedImage(IplImage* imgHSV){       
    IplImage* imgThresh=cvCreateImage(cvGetSize(imgHSV),IPL_DEPTH_8U, 1);
    cvInRangeS(imgHSV, cvScalar(100,150,0), cvScalar(120,255,255), imgThresh); 
    return imgThresh;
}

void trackObject(IplImage* imgThresh){

    CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
    cvMoments(imgThresh, moments, 1);
    double moment10 = cvGetSpatialMoment(moments, 1, 0);
    double moment01 = cvGetSpatialMoment(moments, 0, 1);
    double area = cvGetCentralMoment(moments, 0, 0);

   
    if(area>1000){
        
        int posX = moment10/area;
        int posY = moment01/area;        
        
       if(lastX>=0 && lastY>=0 && posX>=0 && posY>=0)
        {
            
            cvLine(imgTracking, cvPoint(posX, posY), cvPoint(lastX, lastY), cvScalar(0,0,255), 4);
        }

         lastX = posX;
        lastY = posY;
    }

     free(moments); 
}


int main(){
   
      CvCapture* capture =0;       
      capture = cvCaptureFromCAM(0);
      if(!capture){
         printf("Capture failure\n");
         return -1;
      }
      
      IplImage* frame=0;
      frame = cvQueryFrame(capture);           
      if(!frame) return -1;
   
     
     imgTracking=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U, 3);
     cvZero(imgTracking); 

     cvNamedWindow("Video");     
     cvNamedWindow("Track");

      //iterate through each frames of the video     
      while(true){

            frame = cvQueryFrame(capture);           
            if(!frame) break;
            frame=cvCloneImage(frame); 
            
            

            IplImage* imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3); 
            cvCvtColor(frame, imgHSV, CV_BGR2HSV); //Change the color format from BGR to HSV
            IplImage* imgThresh = GetThresholdedImage(imgHSV);
          
            
            
      
           trackObject(imgThresh);

            // Add the tracking image and the frame
           cvAdd(frame, imgTracking, frame);

            cvShowImage("Track", imgThresh);           
           cvShowImage("Video", frame);
           
          
           cvReleaseImage(&imgHSV);
           cvReleaseImage(&imgThresh);            
           cvReleaseImage(&frame);

        
            int c = cvWaitKey(10);
            if((char)c==27 ) break;      
      }

      cvDestroyAllWindows() ;
      cvReleaseImage(&imgTracking);
      cvReleaseCapture(&capture);     

      return 0;
}