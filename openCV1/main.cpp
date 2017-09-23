//Author: Haroun Ansari
//Date: 4/28/2017

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <fstream> 

using namespace std;
using namespace cv; //openCV lib standard


/** Function Headers */
void detectAndDisplay(Mat frame);

/** Global variables */
String face_cascade_name, eyes_cascade_name; // needed for communication between functions
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";

/** @function main */
int main(int argc, const char** argv)
{

	face_cascade_name = "haarcascade_frontalface_alt.xml"; // openCV XML values for face detection
	eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml"; // openCV XML values for eye detection
	VideoCapture capture; //capture object

	vector<int> compression_params; //vector data structure using C STL
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION); //compression used for init data in vector
	compression_params.push_back(9);

	Mat frame; //Mat obj frame
	int num_frames = 100; //number of frames were storing in queue
	time_t start, end; // used for timer

	//-- 1. Load the cascades
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return -1; };//error checking
	if (!eyes_cascade.load(eyes_cascade_name)) { printf("--(!)Error loading eyes cascade\n"); return -1; };

	//-- 2. Read the video stream
	capture.open(0);
	if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }//error checking

	time(&start); // start timer
	while (capture.read(frame)) //occuring as long as openCV is capturing data
	{
		

		if (frame.empty()) 
		{
			printf(" --(!) No captured frame -- Break!");
			break;
		}

		//-- 3. Apply the classifier to the frame
		detectAndDisplay(frame); 

		char c = (char)waitKey(10); 
		if (c == 27) { //when wink detected
			imwrite("output.png", frame, compression_params); // output picture
			break; } // escape
		
		
		
	}
	
		ofstream ofs("output.txt", ios::out | ios::app); // sends frame data to output file
		time(&end); // end timer

		// Time elapsed
		double seconds = difftime(end, start);
		ofs << "Time taken : " << seconds << " seconds" << endl; //outputs time taken

		ofs << "N = " << num_frames << " frames" << endl; //outputs frame number

		ofs << "t-N+1 = " << seconds - num_frames + 1 << endl; //end value

		cout << "Output file 'output.txt' created" << endl;
		cout << "Output picture 'output.png' created" << endl;

		
	
	return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;
	int count;
	bool extra_credit = false; // if you want to test extra credit uncomment next line and comment this line out
	//bool extra_credit = true; //if you want to test extra credit ucomment this line and comment out previous line
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++) //takes in face data such as size and shape
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2); //circumference, width, and height used
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0); // creates an ellipse to put around face

		Mat faceROI = frame_gray(faces[i]); //puts ellipse over face
		std::vector<Rect> eyes;

		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30)); // take in eye data within face element

		for (size_t j = 0; j < eyes.size(); j++)
		{
			Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2); // eye circumference, height and width search
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25); // uses smaller circle radius to detect eyes
			circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0); // creates circle to surround eyes
		}
	}
	while (extra_credit == true) { //secret of universe mode
	}
	imshow(window_name, frame);
	
}
