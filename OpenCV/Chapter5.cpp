#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////// Warp Images //////////////////////

float w = 250, h = 350;
Mat matrix, matrixQ, imgWarp, imgWarpQ;

void main() {


	string path = "Resources/cards.jpg";
	Mat img = imread(path);

	// King card
	Point2f src[4] = { {529,142}, {771,190}, {405,395}, {674,457} };
	Point2f dst[4] = { {0.0f,0.0f}, {w,0.0f}, {0.0f,h}, {w,h} };

	// Queen card
	Point2f srcQ[4] = { {63,323}, {340,278}, {89,634}, {404,574} };
	Point2f dstQ[4] = { {0.0f,0.0f}, {w,0.0f}, {0.0f,h}, {w,h} };

	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w,h));

	matrixQ = getPerspectiveTransform(srcQ, dstQ);
	warpPerspective(img, imgWarpQ, matrixQ, Point(w, h));

	imshow("Image", img);
	imshow("Image Warp", imgWarp);
	imshow("Image Warp Queen", imgWarpQ);
	waitKey(0);

}