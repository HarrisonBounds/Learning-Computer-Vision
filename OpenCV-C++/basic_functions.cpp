#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void grayscale(Mat img);
void blur(Mat img);
void edgeDetection(Mat img);
void dilate_and_erode(Mat img);

//Learning how to convert an image to grayscale, blur an image, detect edges, dilate an image, and erode an image

int main() {
	string path = "Resources/temple.jpg";
	Mat img = imread(path);

//	grayscale(img);
//	blur(img);
//	edgeDetection(img);
	dilate_and_erode(img);


}

void grayscale(Mat img) {
	Mat imgGray; //Define the grayscale iamge name
	

	//After reading the image, you can convert it into grayscale
	cvtColor(img, imgGray, COLOR_BGR2GRAY); //Parameters: input image, output image, and conversion

	//Show Images
	imshow("Image", img);
	imshow("Grayscale Image", imgGray);
	
	waitKey(0);
}

void blur(Mat img) {
	Mat imgBlur;

	GaussianBlur(img, imgBlur, Size(15, 15), 5, 0); //Parameters: input image, output image, kernel size (widthxheight), sigmaX, sigmaY

	//Show Images
	imshow("Image", img);
	imshow("Blur Image", imgBlur);

	waitKey(0);
}

void edgeDetection(Mat img) {
	Mat imgBlur;
	Mat imgCanny;
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0); //Common practice to blur the image slightly to make it easier to detect edges

	Canny(imgBlur, imgCanny, 50, 150); //Parameters: input image, output image, threshhold 1, threshhold 2

	imshow("Image", img);
	imshow("Image Canny", imgCanny);

	waitKey(0);
}

void dilate_and_erode(Mat img) {
	Mat imgBlur, imgCanny;
	Mat imgDilate, imgErode;
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 50, 150);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5)); //Create a kernel that can be used with dilation : Increasing the size will dilate the image more : Use only odd numbers

	dilate(imgCanny, imgDilate, kernel);
	erode(imgDilate, imgErode, kernel);

	imshow("Image with Edge Detection", imgCanny);
	imshow("Dilated Image", imgDilate);
	imshow("Eroded Image", imgErode);

	waitKey(0);
}
