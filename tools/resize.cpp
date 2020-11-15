#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;

void resize_image(const std::string & inFilename, const std::string & outFilename, cv::Size new_size)
{
    cv::Mat img = cv::imread(inFilename);
    cv::imshow("Now Processing...", img);
    cv::resize(img, img, new_size);
    cv::imwrite(outFilename, img);
}

int main(int argc, char *argv[])
{
    std::string input_path;
    std::string output_path = "output";
    if (argc > 1) input_path = argv[1];
    else {
        std::cout << "Please assign the root directory of images: ";
        std::cin >> input_path;
    }
    //if (argc > 2) output_path = argv[2];
    //else {
    //    std::cout << "Please assign the output directory of images: ";
    //    std::cin >> output_path;
    //}
    if (!fs::exists(input_path)) {
        std::cerr << "Directory \'" << input_path << "\' not found!";
    } else if (!fs::is_directory(input_path)) {
        std::cerr << "\'" << input_path << "\' is not a directory!";
    } else {
        std::cout << "SRC: " << input_path << std::endl;
    }
    //if (!fs::exists(output_path)) {
    //    std::cerr << "Directory \'" << output_path << "\' not found!" << std::endl;
    //} else if (!fs::is_directory(output_path)) {
    //    std::cerr << "\'" << output_path << "\' is not a directory!" << std::endl;
    //} else {
    //    std::cout << "DST: " << output_path << std::endl;
    //}
    int x = 256, y = 256;
    std::cout << "Please assign aimed image size: \n";
    std::cout << "Width : "; std::cin >> x;
    std::cout << "Height: "; std::cin >> y;
    cv::Size new_size(x, y);
    cv::namedWindow("Now Processing...", cv::WINDOW_NORMAL);
    for (fs::recursive_directory_iterator it(input_path); it != fs::end(it); ++it)
    {
        if (!fs::is_directory(it->status())) // only operate on files
        {
            auto it_extension = it->path().extension();
            if (it_extension == ".png" || it_extension == ".jpg" || it_extension == ".jpeg") {
                std::cout << "Now processing " << it->path() << std::endl;
                try {
                    std::string in = it->path().string();
                    std::string out = it->path().string();
                    resize_image(in, out, new_size);
                }
                catch (cv::Exception & cv_except) {
                    std::cerr << cv_except.what() << std::endl;
                }
            }
        }
        else continue; // not files
    }
    return 0;
}
