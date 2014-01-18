#include <iostream>
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\opencv.hpp"

using namespace std;
using namespace cv;

int main(){
	Mat im_gray=imread("1.png", CV_LOAD_IMAGE_GRAYSCALE);
	namedWindow("N");
	imshow("N", im_gray);
	waitKey(0);
	Mat im_bw =im_gray>150;//threshold
	namedWindow("bw");
	imshow("bw", im_bw);
	waitKey(0);

	return 0;

}