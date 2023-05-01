#include <iostream>
#include <chrono>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

inline void resizeImage(cv::Mat &imageToResize, int maxSize, double scaleFactor)
{   
    int width = imageToResize.cols;
    int height = imageToResize.rows;

    if(width <= maxSize && height <= maxSize)
        return;
    
    if(width < height)
    {
        int newWidth = static_cast<int>(width / (1.0 * height / maxSize) );
        cv::resize(imageToResize, imageToResize, cv::Size(newWidth * scaleFactor, maxSize));
    }
    else
    {
        int newHeight = static_cast<int>(height / (1.0 * width / maxSize));
        cv::resize(imageToResize, imageToResize, cv::Size(maxSize * scaleFactor, newHeight));
    }
    
}

inline char getSymbolFromGrayValue(int value)
{
    const size_t countOfSymbols = 10;
    const char asciiTable[countOfSymbols] = {'.', ',', ':', '+', '*', '?', '%', '$', '#', '@'};
    const int index = static_cast<int>(1.0 * value * (countOfSymbols - 1) / 255);
    return asciiTable[index];
}

int main(int argc, char **argv)
{
    cv::VideoCapture cap(argv[1]);

    if(!cap.isOpened())
    {
        std::cout << "No video file: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    const int fps = cap.get(cv::CAP_PROP_FPS);

    while(true)
    {

        cv::Mat img;
        cap >> img;

        if(img.empty())
            return -1;

        const int consoleWidth = 150;
        const double scale = 1.3;
        resizeImage(img, consoleWidth, scale);
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

        for(int y = 1; y < img.rows; ++y)
        {
            cv::Vec<uchar, 1> *pixrow = img.ptr<cv::Vec<uchar, 1>>(y);
            for(int x = 1; x < img.cols; ++x)
            {
                int gray = pixrow[x][0];
                std::cout << getSymbolFromGrayValue(gray);
            }
            std::cout << std::endl;
        }  

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));  
        system("clear");
    }
        
    return EXIT_SUCCESS;
}
