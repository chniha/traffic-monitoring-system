
# traffic-monitoring-system
Vehicle detection and counting using C++ and OpenCV
# AI-Based Traffic Monitoring and Vehicle Counting System

This project implements a traffic monitoring system that detects and counts vehicles from a traffic video using Computer Vision techniques. The system uses OpenCV with C++ and YOLO object detection to identify vehicles such as cars, buses, and trucks and maintain a count of vehicles passing through a defined area.

## Features
- Vehicle detection using YOLO
- Vehicle counting from traffic video
- Real-time frame processing using OpenCV
- Supports multiple vehicle types

## Technologies Used
- C++
- OpenCV
- YOLO (You Only Look Once) Object Detection
- Computer Vision

## Project Files
- `test1.cpp` – Main program for vehicle detection and counting
- `yolov3.cfg` – YOLO configuration file
- `coco.names` – Class labels for object detection

## Requirements
- OpenCV installed
- C++ compiler (GCC / CodeBlocks / Visual Studio)
- YOLO weight file

## Required Files (Not Uploaded)
Due to GitHub file size limits, the following files are not included in the repository.

Download them manually:
- YOLO Weights: https://pjreddie.com/media/files/yolov3.weights
- Sample traffic video: Any traffic video renamed as `traffic.mp4`

Place these files in the project directory before running the program.

## How to Run
1. Install OpenCV on your system.
2. Download the YOLO weights file.
3. Place `yolov3.weights` and `traffic.mp4` in the project folder.
4. Compile the C++ program.
5. Run the program to detect and count vehicles from the video.

## Applications
- Smart traffic monitoring
- Traffic flow analysis
- Smart city systems
- Automated vehicle counting

## Author
Niharika C  
B.Tech Computer Science Engineering
