#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	//Create a Blank Image 
	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255)); //Parameters : width, height, num bits + signed/unsigned + num of channels, BGR values as a scalar

	circle(img, Point(256, 256), 155, Scalar(255, 0, 0), FILLED); // Parameters : input image, center point of the circle, radius of the circle, BGR values as a scalar, line thickness/FILLED

	rectangle(img, Point(130, 230), Point(390, 290), Scalar(20, 50, 88), 5); // Parameters same as circle, but you specify the top left point and bottom right point

	line(img, Point(10, 400), Point(400, 10), Scalar(39, 12, 209), 10); //Specify the starting point and ending point of the line

	putText(img, "Learning OpenCV with C++", Point(50, 450), FONT_HERSHEY_TRIPLEX, 0.75, Scalar(30, 200, 30), 3); //input, text, Top left point, font, font scale, BGR, thickness

	imshow("Created Image", img);

	waitKey(0);
}