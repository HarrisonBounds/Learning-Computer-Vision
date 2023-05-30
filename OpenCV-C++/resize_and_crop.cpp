#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void resize(Mat img);
void scale(Mat img);
void crop(Mat img);

int main() {
	string path = "Resources/temple.jpg";
	Mat img = imread(path);

	Mat imgResized;

	//Print the current size of the image
	cout << "Image Size: " << img.size() << endl;

//	resize(img);
//	scale(img);
	crop(img);

	
}

void resize(Mat img) {
	Mat imgResized;

	resize(img, imgResized, Size(640, 480)); //Parameters : input image, output image, output image size

	//You can also scale an image down to keep its aspect ratio
	resize(img, imgResized, Size(), 0.5, 0.5); //Keep size empty and define a scaling size for x and y

	imshow("Image", img);
	imshow("Resized Image", imgResized);

	waitKey(0);
}

void scale(Mat img) {
	Mat imgScaled;

	//You can also scale an image down to keep its aspect ratio
	resize(img, imgScaled, Size(), 0.5, 0.5); //Keep size empty and define a scaling size for x and y

	imshow("Image", img);
	imshow("Scaled Image", imgScaled);

	waitKey(0);
}

void crop(Mat img) {
	//ROI - Region of Interest
	Mat imgCropped;

	Rect roi(50, 10, 1000, 1100); //Rectangular crop : Parameters : point x, point y, width, height
	imgCropped = img(roi); //Inserting the crop into our image and storing it in the imgCropped variable

	imshow("Image", img);
	imshow("Cropped Image", imgCropped);

	waitKey(0);
}