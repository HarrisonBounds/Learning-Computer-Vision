#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//Pass in two images, the dilated image and the image that we want to draw on(original image)
void getContours(Mat imgDilate, Mat img) {

	vector<vector<Point>> contours; //Vector of Points
	vector<Vec4i> hierarchy; //Vector containing 4 integers
	

	findContours(imgDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //Parameters : input image, detected contours, output vector, contour retrieval mode, contour approximation method
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
	

	//Remove the noise by calculating the area of the contours and setting a threshhold : Also find bounding box around each shape
	for (int i = 0; i < contours.size(); i++) {

		int area = contourArea(contours[i]); //Calculates the area of the contour giving a specific contour as an input
		cout << "Area: " << area << endl;

		vector<vector<Point>> conPoly(contours.size()); //Will hold only the points located at the corners of the shape : Cannot exceed the size of the contours
		vector<Rect> boundRect(contours.size()); //Stores the rectangle values of the shapes
		string objectType;

		if (area > 1000) { //Setting the threshold
			float perimeter = arcLength(contours[i], true); //Calculate the contours perimeter : takes in which contour to calculate, whether the curve is closed or not
			//Figure out the shape based on the number of edges
			approxPolyDP(contours[i], conPoly[i], 0.02*perimeter, true); //appoximates a polygons curves : input vector, output vector, approximation accuracy (episilon), closed curve(bool)
			
			cout << "Number of edges: " << conPoly[i].size() << endl; //This is the number of edges/corner points it has found : we can use this to determine what the shape is
			
			//Draw the rectangle around the shapes
			boundRect[i] = boundingRect(conPoly[i]); //Function that finds the bounding rectangle around the shape
			

			int objCorner = (int)conPoly[i].size(); //Store the number of corner points into an interger for each iteration so we can determine the shape

			if (objCorner == 3) {
				objectType = "Triangle";
			}
			else if (objCorner == 4) {
				//Tell the difference between square and rectangle
				float aspectRatio = (float)boundRect[i].width / (float)boundRect[i].height; //If this is 1, then the shape is a square because the width and height should be the same
				if (aspectRatio > 0.95 && aspectRatio < 1.05) { //Handling small errors
					objectType = "Square";
				}
				else {
					objectType = "Rectangle";
				}
			}
			else if (objCorner > 4) {
				objectType = "Circle";
			}
			else {
				objectType = "IDK";
			}

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2); //Parameters : input image, all input contours, contour to draw, color, thickness
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5); //Draw a bounding box around the shapes
			putText(img, objectType, { boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_COMPLEX_SMALL, 0.75, Scalar(100, 150, 120), 1); //Label the shapes
		}
	}
}

int main() {
	Mat imgGray, imgBlur, imgCanny, imgDilate;

	string path = "Resources/shapes.png";
	Mat img = imread(path);

	//Need to preprocess the image before we can find the shape
	//If we can find the edges, we can figure out which shape is that specific edge
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDilate, kernel);

	getContours(imgDilate, img);

	imshow("Image", img);
	/*imshow("Image Canny", imgCanny);
	imshow("Image Dilated", imgDilate);*/ //Shape detection will be much easier with a dilated image, since it makes the edges easier to see
	waitKey(0);
}