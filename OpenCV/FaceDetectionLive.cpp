#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


void main() {

	VideoCapture cap(0);
	Mat img;

	while (true) {

		cap.read(img);

		CascadeClassifier faceCascade;

		faceCascade.load("Resources/haarcascade_frontalface_default.xml");

		if (faceCascade.empty()) { cout << "xml file is not loaded" << endl; }

		vector <Rect> faces;
		faceCascade.detectMultiScale(img, faces, 1.1, 10);

		for (int i = 0; i < faces.size(); i++) {

			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(25, 255, 255), 3);
			putText(img, "Detect!", { faces[i].x, faces[i].y - 5 }, FONT_HERSHEY_TRIPLEX, 1.5, Scalar(0, 69, 255), 1);

		}

		imshow("Image", img);
		waitKey(1);

	}

}