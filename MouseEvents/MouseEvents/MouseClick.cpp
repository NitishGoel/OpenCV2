#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2\core\core.hpp"

using namespace std;
using namespace cv;


void MyFilledCircleRed(Mat, Point);
void MyFilledCircleBlue(Mat, Point);
void MyFilledCircleGreen(Mat, Point);

Mat image=imread("1.jpg");

	void CallBackFunc(int event,int x,int y,int flags,void* userdata){
	
		if( event == EVENT_LBUTTONDOWN){
			cout<<"the left mouse button was clicked at ("<<x<<","<<y<<")"<<endl;
			MyFilledCircleRed(image, Point(x,y));
		
		}

		if(event == EVENT_RBUTTONDOWN){
			cout<<"the right mouse button was clicked at ("<<x<<","<<y<<")"<<endl;
			MyFilledCircleGreen(image, Point(x,y));
		
		}
	
		if(event == EVENT_MBUTTONDOWN){
		cout<<"the middle mouse button was clicked at ("<<x<<","<<y<<")"<<endl;
		MyFilledCircleBlue(image, Point(x,y));	
		
		}

		if(event == EVENT_MOUSEMOVE){
		cout<<"mouse moved over the window position ("<<x<<","<<y<<")"<<endl;
		imshow("nitish", image);	
		

		}
	
	}

	int main(){
		
		namedWindow("nitish",1);
        setMouseCallback("nitish",CallBackFunc,NULL);
		imshow("nitish", image);
		
		int x= waitKey(0);
		if(x==27)return -1;
		return 0;
}

	void MyFilledCircleRed( Mat img , Point center )
{
        int thickness = -1;
        int lineType = 8;
        circle( img, center, 5, Scalar( 0, 0, 255 ), thickness, lineType );
		imshow("nitish", image);
}

	void MyFilledCircleGreen( Mat img , Point center )
{
        int thickness = -1;
        int lineType = 8;
        circle( img, center, 5, Scalar( 0, 255, 0 ), thickness, lineType );
		imshow("nitish", image);
}

	void MyFilledCircleBlue( Mat img , Point center )
{
        int thickness = -1;
        int lineType = 8;
        circle( img, center, 5, Scalar( 255, 0, 0 ), thickness, lineType );
		imshow("nitish", image);
}