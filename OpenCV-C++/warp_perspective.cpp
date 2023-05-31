#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat matrix, imgWarp;
	float width = 250, height = 350; //Height of a playing card (trying to keep the same aspect ratio)

	string path = "Resources/cards.jpg";
	Mat img = imread(path);

	//You can edit in Paint to see the exact point of where the cursor is
	//Top left = 205, 650 : Bottom Left = 135, 845 : Top Right = 370, 645 : Bottom Right = 325, 840

	Point2f src[4] = { {205, 650}, {135, 845}, {370, 645}, {325, 840} }; //Define an array of floating point Points
	Point2f dest[4] = { {0.0f, 0.0f}, {0.0f, height}, {width, 0.0f}, {width, height} }; //An array of corresponding points to translate (Destination points) (0.0f means float value)

	//Matrix to transform to find the warp
	matrix = getPerspectiveTransform(src, dest); //Gives us a matrix to input values and output corresponding values
	warpPerspective(img, imgWarp, matrix, Point(width, height)); //Takes the matrix and warps it into a usable image with a width and height

	//Create circles around the points of the cards
	for (int i = 0; i < 4; i++) {
		circle(img, src[i], 10, Scalar(255, 0, 0), FILLED);
	}

	imshow("Image", img);
	imshow("Image Warp", imgWarp);

	waitKey(0);
}