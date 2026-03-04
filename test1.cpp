#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace cv;
using namespace std;
using namespace dnn;

int main()
{
    VideoCapture cap("traffic.mp4");

    if(!cap.isOpened())
    {
        cout<<"Error opening video"<<endl;
        return -1;
    }

    Net net = readNet("yolov3.weights","yolov3.cfg");

    vector<string> classNames;
    ifstream file("coco.names");
    string name;

    while(getline(file,name))
        classNames.push_back(name);

    Mat frame;

    int vehicleCount = 0;
    int linePosition = 350;

    vector<Point> countedCentroids;

    while(true)
    {
        cap >> frame;

        if(frame.empty())
            break;

        resize(frame,frame,Size(800,600));

        Mat blob = blobFromImage(frame,1/255.0,Size(416,416),Scalar(),true,false);
        net.setInput(blob);

        vector<Mat> outputs;
        net.forward(outputs, net.getUnconnectedOutLayersNames());

        vector<Rect> boxes;
        vector<float> confidences;

        for(auto &output : outputs)
        {
            for(int i=0;i<output.rows;i++)
            {
                float confidence = output.at<float>(i,4);

                if(confidence > 0.5)
                {
                    int centerX = output.at<float>(i,0)*frame.cols;
                    int centerY = output.at<float>(i,1)*frame.rows;
                    int width   = output.at<float>(i,2)*frame.cols;
                    int height  = output.at<float>(i,3)*frame.rows;

                    int left=centerX-width/2;
                    int top=centerY-height/2;

                    boxes.push_back(Rect(left,top,width,height));
                    confidences.push_back(confidence);
                }
            }
        }

        vector<int> indices;
        NMSBoxes(boxes,confidences,0.5,0.4,indices);

        for(int i : indices)
        {
            Rect box = boxes[i];

            rectangle(frame,box,Scalar(0,255,0),2);

            int centerX = box.x + box.width/2;
            int centerY = box.y + box.height/2;

            Point centroid(centerX,centerY);

            circle(frame,centroid,5,Scalar(0,0,255),-1);

            bool alreadyCounted = false;

            for(Point p : countedCentroids)
            {
                if(norm(p - centroid) < 50)
                {
                    alreadyCounted = true;
                    break;
                }
            }

            if(!alreadyCounted && centerY > linePosition)
            {
                vehicleCount++;
                countedCentroids.push_back(centroid);
            }
        }

        cv::line(frame,Point(0,linePosition),Point(frame.cols,linePosition),Scalar(255,0,0),2);

        putText(frame,
                "Vehicle Count: "+to_string(vehicleCount),
                Point(20,50),
                FONT_HERSHEY_SIMPLEX,
                1,
                Scalar(0,0,255),
                2);

        imshow("Traffic Monitoring System",frame);

        if(waitKey(30)==27)
            break;
    }

    cap.release();
    destroyAllWindows();
}