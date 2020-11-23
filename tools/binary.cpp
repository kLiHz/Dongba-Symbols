#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat gray(cv::Mat & input) {
    cv::Mat grayImg;
    cv::cvtColor(input, grayImg, cv::COLOR_BGR2GRAY);
    return grayImg;
}

cv::Mat binary(cv::Mat & input) {
    cv::Mat result;
    cv::threshold(input, result, 40, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    return result;
}

int main(int argc, char * argv[]) {
    cv::String imgName("sample.jpg"); // by default
    if (argc > 1) {
        imgName = argv[1];
    }
    cv::Mat img = cv::imread(imgName);
    if (img.empty()) {
        std::cerr << "Cannot read the image: " << imgName << std::endl;
        return -1;
    }
    cv::Mat grayImg = gray(img);
    cv::Mat result = binary(grayImg);
    cv::namedWindow("Src", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Gray", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Binary", cv::WINDOW_AUTOSIZE);
    cv::imshow("Src", img);
    cv::imshow("Gray", grayImg);
    cv::imshow("Binary", result);
    cv::waitKey(0);
    return 0;
}
