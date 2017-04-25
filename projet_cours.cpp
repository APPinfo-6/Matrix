#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, processed_img;

int currentSize = 0;
int Alpha = 10;
int Beta = 100;

const int MaxSize = 20;
const int MaxAlpha = 20;
const int MaxBeta = 200;

float fx;
float fy;

// Read image from the path
int readImage(cv::Mat& img, const std::string& filename, const std::string& output_name)
{
    std::cout << output_name << " => " << filename << std::endl;
    img = cv::imread(filename);

    if(img.empty())
    {
        std::cerr << "Cannot read image file!" << filename << std::endl;
        return -1;
    }

    return 0;
}

// Image erosion
void Erosion(int, void*)
{
    int erosion_type;
    erosion_type = MORPH_RECT;

    Mat element = getStructuringElement(erosion_type,
                                        Size(2*currentSize+1, 2*currentSize+1),
                                        Point(currentSize, currentSize));
    erode(img, processed_img, element);

    imshow("Image Erosion & Dilation", processed_img);
}

// Image dilation
void Dilation(int, void*)
{
    int dilation_type;
    dilation_type = MORPH_RECT;

    Mat element = getStructuringElement(dilation_type,
                                        Size(2*currentSize+1, 2*currentSize+1),
                                        Point(currentSize, currentSize));
    dilate(img, processed_img, element);

    imshow("Image Erosion & Dilation", processed_img);
}

// Lighten or darken image, based on two parameters
void Lighten(int, void*)
{
    processed_img = Mat::zeros(img.size(),img.type());

    for (int i = 0;i<img.rows;++i)
        for(int j= 0;j<img.cols;++j)
            for(int k = 0;k<3;++k)
                processed_img.at<Vec3b>(i,j)[k] = saturate_cast<uchar>(img.at<Vec3b>(i,j)[k]*(Alpha*0.1)+(Beta-100));

    imshow("Image Lightening", processed_img);
}

//Image resizing
void Resize(int, void*)
{
    if((fx < 1.0) && (fy < 1.0))
    {
        resize(img, processed_img, Size(), fx, fy, INTER_AREA);
    }

    resize(img, processed_img, Size(), fx, fy, INTER_CUBIC);

    imshow("Original Image", img);
    imshow("Resize Image", processed_img);
}

int main(int argc, char** argv)
{
    // Load image
    readImage(img, argv[1], "Original Image");

    if(argc < 2)
    {
        std::cerr << "Error : you must specify the image file name in command lines" << std::endl;
        return -1;
    }

    // Load menu
    cout << "Welcome to our image-processing program!" << endl;
    cout << "--------------------MENU--------------------" << endl;
    cout << "1 Erose and Dilate" << endl;
    cout << "2 Lighten and Darken" << endl;
    cout << "3 Resize" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Please enter a number in order to choose the function: ";

    // User needs to give a input
    int choice;
    cin >> choice;

    // Execute the function according to the number given
    switch(choice)
    {
        case 1:
            namedWindow( "Image Erosion & Dilation", CV_WINDOW_AUTOSIZE );

            createTrackbar("Erosion Size", "Image Erosion & Dilation",
                           &currentSize, MaxSize,
                           Erosion);
            createTrackbar("Dilation Size", "Image Erosion & Dilation",
                           &currentSize, MaxSize,
                           Dilation);

            // Default start
            Erosion(0, 0);
            Dilation(0, 0);

            // Wait for a key stroke
            waitKey(0);
                break;

        case 2:
            namedWindow( "Image Lightening", CV_WINDOW_AUTOSIZE );

            createTrackbar("Beta", "Image Lightening",
                           &Beta, MaxBeta,
                           Lighten);
            createTrackbar("Alpha", "Image Lightening",
                           &Alpha, MaxAlpha,
                           Lighten);

            Lighten(0, 0);

            waitKey(0);
                break;

        case 3:
            std::cout << "Please input fx" << endl;
            std::cin >> fx;
            std::cout << "Please input fy" << endl;
            std::cin >> fy;

            namedWindow( "Original Image", CV_WINDOW_AUTOSIZE );
            namedWindow( "Resize Image", CV_WINDOW_AUTOSIZE );

            Resize(0, 0);

            waitKey(0);
                break;

        default:
            std::cout << "This is not a choice." << endl;
        }

    return 0;
}
