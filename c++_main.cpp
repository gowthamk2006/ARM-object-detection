#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace cv;
using namespace cv::dnn;
using namespace std;

// Class labels for MobileNet-SSD
string classNames[] = {
    "background", "aeroplane", "bicycle", "bird", "boat",
    "bottle", "bus", "car", "cat", "chair",
    "cow", "diningtable", "dog", "horse",
    "motorbike", "person", "pottedplant",
    "sheep", "sofa", "train", "tvmonitor"
};

// Helper: current timestamp
string currentTimestamp()
{
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm *ltm = localtime(&now_time);

    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

int main()
{
    // Open log file (append mode)
    ofstream logFile("detection.log", ios::app);
    if (!logFile.is_open())
    {
        cout << "ERROR: Cannot open log file\n";
        return -1;
    }

    logFile << "\n===== NEW SESSION START =====\n";

    // Load CNN model
    Net net = readNetFromCaffe(
        "MobileNetSSD_deploy.prototxt",
        "MobileNetSSD_deploy.caffemodel"
    );

    if (net.empty())
    {
        cout << "ERROR: Could not load CNN model\n";
        return -1;
    }

    // Open webcam
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "ERROR: Cannot open webcam\n";
        return -1;
    }

    Mat frame;

    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;

        system("clear");
        cout << "LIVE OBJECT DETECTION (Name + Confidence)\n";
        cout << "----------------------------------------\n";

        // ---- Start latency timer ----
        auto t_start = chrono::high_resolution_clock::now();

        Mat blob = blobFromImage(
            frame,
            0.007843,
            Size(300, 300),
            Scalar(127.5, 127.5, 127.5),
            false
        );

        net.setInput(blob);
        Mat detections = net.forward();

        auto t_end = chrono::high_resolution_clock::now();
        double latency_ms =
            chrono::duration<double, milli>(t_end - t_start).count();

        Mat detectionMat(
            detections.size[2],
            detections.size[3],
            CV_32F,
            detections.ptr<float>()
        );

        bool anyDetection = false;

        for (int i = 0; i < detectionMat.rows; i++)
        {
            float confidence = detectionMat.at<float>(i, 2);

            if (confidence > 0.3)
            {
                anyDetection = true;

                int classId = (int)detectionMat.at<float>(i, 1);

                int x1 = (int)(detectionMat.at<float>(i, 3) * frame.cols);
                int y1 = (int)(detectionMat.at<float>(i, 4) * frame.rows);
                int x2 = (int)(detectionMat.at<float>(i, 5) * frame.cols);
                int y2 = (int)(detectionMat.at<float>(i, 6) * frame.rows);

                rectangle(frame, Point(x1, y1), Point(x2, y2),
                          Scalar(0, 255, 0), 2);

                string label = classNames[classId] + " : " +
                               to_string(int(confidence * 100)) + "%";

                putText(frame, label,
                        Point(x1, y1 - 10),
                        FONT_HERSHEY_SIMPLEX,
                        0.6,
                        Scalar(0, 255, 0),
                        2);

                // ---- Terminal output ----
                cout << left << setw(12)
                     << classNames[classId]
                     << " : "
                     << setw(3)
                     << int(confidence * 100)
                     << "%  | Latency: "
                     << fixed << setprecision(2)
                     << latency_ms << " ms\n";

                // ---- Log file output ----
                logFile << "[" << currentTimestamp() << "] "
                        << classNames[classId] << " "
                        << int(confidence * 100) << "% "
                        << "latency=" << fixed << setprecision(2)
                        << latency_ms << " ms\n";
            }
        }

        if (!anyDetection)
        {
            cout << "No objects detected\n";
        }

        imshow("Multi-Object CNN Detection", frame);

        if (waitKey(1) == 27)
            break;

        usleep(100000);
    }

    cap.release();
    destroyAllWindows();
    logFile.close();

    return 0;
}
