#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat imgHSV, mask;

	//Hardcoding these values can be a pain to find the exact color, so we will use a track bar instead
	int hmin = 0, smin = 110, vmin = 153;
	int hmax = 19, smax = 240, vmax = 255;

	//NOTE: The max value for hue is 180, while for the other two values it is 255

	string path = "Resources/lambo.png";
	Mat img = imread(path);

	//Convert our image to the HSV (Hue, Saturation, Value) Space to make it easier to read color
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	//Create the track window : named window creates a window as a placholder for images and trackbars
	namedWindow("Trackbars", (640, 200));

	//Create trackbars : Use these to find the exact value of the color in images to detect them
	createTrackbar("Hue Min", "Trackbars", &hmin, 179); //Parameters : Name of trackbar, name of window to place it in, address of value, max value of track bar
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true) {
		//Define lower and upper limit
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);


		//Use the inrange function to collect our color
		inRange(imgHSV, lower, upper, mask);//Parameters : input image, lower HSV limit, upper HSV limit, output image

		imshow("Image", img);
		imshow("HSV Image", imgHSV);
		imshow("Image Mask", mask);
		waitKey(1);
	}
	
}