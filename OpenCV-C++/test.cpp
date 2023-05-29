#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	string path = "Resources/banana.png";
	Mat img = imread(path);
	imshow("Image", img);
	waitKey(0);
	return 0;
}