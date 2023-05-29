#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void image();
void video();
void webcam();

int main() {
	//image();
	//video();
	webcam();
}

//Showing an Image
void image() {
	//Define our path
	string path = "Resources/banana.png";

	//Import our image
	Mat img = imread(path); //Mat is a matrix data type that handles the images : imread reads the image from the specified path

	//Show our image
	imshow("Image", img); //SHows the image with an inout for the window name and what image to show. By deafult, it opens and closes automatically

	waitKey(0); //Waits for a key to be pressed so our image can be shown until we decide to stop it : 0 means infinite time
}

//Showing a video : Think of this as a continous stream of images
void video() {
	string path = "Resources/spinner.mp4";
	VideoCapture cap(path); //Specify the path to the video
	Mat img;

	while (true) {
		//Read each image one by one
		cap.read(img); 

		//SHow each image one by one
		imshow("Image", img); 

		//Wait for the image
		waitKey(15); //milliseconds
	}
	//Whenever the video finishes, it gives you an error because there are no more images to display
}

//Showing a webcam
void webcam() {
	VideoCapture cap(0); //Specify the path to the webcam : if you only have 1 webcam, you can put 0
	Mat img;

	while (true) {
		//Read each image one by one
		cap.read(img);

		//SHow each image one by one
		imshow("Image", img);

		//Wait for the image
		waitKey(1); //milliseconds
	}
}


