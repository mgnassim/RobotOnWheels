#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class FaceDetection {
public:
    int detectFace() {
        // Create a video capturing object
        cv::VideoCapture video(0);

        // For saving the frame
        cv::Mat frame;

        // Get resloution
        int frameWidth = video.get(cv::CAP_PROP_FRAME_WIDTH);
        int frameHeight = video.get(cv::CAP_PROP_FRAME_HEIGHT);

        // Check if the video is opend
        if (!video.isOpened()) return -1;

        // Create video writer object
        cv::VideoWriter output("LiveVideo.mp4", cv::VideoWriter::fourcc('a', 'v', 'c', '1'), 3, cv::Size(frameWidth, frameHeight));

        while (video.read(frame)) {

            CascadeClassifier faceCascade;

            faceCascade.load("Resources/haarcascade_frontalface_default.xml");

            if (faceCascade.empty()) { cout << "xml file is not loaded" << endl; }

            vector <Rect> faces;
            faceCascade.detectMultiScale(frame, faces, 1.1, 10);

            for (int i = 0; i < faces.size(); i++) {

                rectangle(frame, faces[i].tl(), faces[i].br(), Scalar(25, 255, 255), 3);
                putText(frame, "Detect!", { faces[i].x, faces[i].y - 5 }, FONT_HERSHEY_TRIPLEX, 1.5, Scalar(0, 69, 255), 1);

            }

            // Display the frame in Visual Studio
            cv::imshow("Video feed", frame);

            // Write the frame to the output
            output.write(frame);

            // Give time to process
            if (cv::waitKey(25) >= 0) {
                break;
            }
        }

        // Release writer and video capture
        output.release();
        video.release();

        cv::destroyAllWindows();
    }
};

int main() {

    FaceDetection face;

    face.detectFace();

    return 0;
}
