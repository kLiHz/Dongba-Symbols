#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <boost/program_options.hpp>

int main(int argc, char* argv[]) {
    int cols, rows, lineWidth, length;
    bool displayOnly;
    std::string filename;
    cv::Vec3b color, background;

try {
    using boost::program_options::value;
    using boost::program_options::options_description;
    using boost::program_options::parse_command_line;
    using boost::program_options::variables_map;

    options_description desc{"Grid Printer v0.0.1"};
    desc.add_options()
            ("help,h", "Print this message.")
            ("display-only", "Display by 'cv::imshow'.")
            ("thickness,b", value<int>()->default_value(1), "Grid line thickness in px.")
            ("length,l", value<int>(&length)->default_value(200), "Length of a side in px.")
            ("cols,c", value<int>(&cols)->default_value(4), "Number of squares in a row.")
            ("rows,r", value<int>(&rows)->default_value(5), "Rows of squares.")
            ("filename,f", value<std::string>(&filename)->default_value("grid.png"), "Output filename.")
            ("fg", value<std::vector<int>>()->multitoken()->composing()->default_value({0,255,0}, "0 255 0"), "Grid line color (RGB).")
            ("bg", value<std::vector<int>>()->multitoken()->composing()->default_value({255,255,255}, "255 255 255"), "Background color (RGB).")
            ;

    variables_map vm;

    boost::program_options::store(parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }

    lineWidth = vm["thickness"].as<int>() * 2 - 1;

    auto f = vm["fg"].as<std::vector<int>>();
    auto b = vm["bg"].as<std::vector<int>>();

    displayOnly = vm.count("display-only");

    color = cv::Vec3b(f[2], f[1], f[0]);
    background = cv::Vec3b(b[2], b[1], b[0]);
    
    std::cout << std::boolalpha;
    std::cout << "Rows:                     " << rows << '\n';
    std::cout << "Cols:                     " << cols << '\n';
    std::cout << "Pixel in length:          " << length << " px \n";
    std::cout << "Grid line width:          " << lineWidth << " px \n";
    std::cout << "Grid line color (RGB):    " << cv::Vec3b(f[0], f[1], f[2]) << '\n';
    std::cout << "Background color (RGB):   " << cv::Vec3b(b[0], b[1], b[2]) << '\n';
    std::cout << "Display Only:             " << displayOnly << "\n";
    std::cout << "Output filename:          " << filename << '\n';
    std::cout << std::noboolalpha;
}
    catch (const boost::program_options::error& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    auto height = rows * length + (rows + 1) * lineWidth;
    auto width = cols * length + (cols + 1) * lineWidth;

    auto canvas = cv::Mat(cv::Size(width, height), CV_8UC3, background);

    for (int i = 0; i <= rows; i += 1) {
        auto y = (length + lineWidth) * i;
        auto tl = cv::Point {0, y};
        auto br = cv::Point {width, y + lineWidth - 1};
        cv::rectangle(canvas, tl, br, color, -1);
    }

    for (int i = 0; i <= cols; i += 1) {
        auto x = (length + lineWidth) * i;
        auto tl = cv::Point {x, 0};
        auto br = cv::Point {x + lineWidth - 1, height};
        cv::rectangle(canvas, tl, br, color, -1);
    }

    if (displayOnly) {
        cv::namedWindow("test", cv::WindowFlags::WINDOW_NORMAL);
        cv::imshow("test", canvas);
        cv::waitKey(0);
    } else {
        cv::imwrite(filename, canvas);
    }
}
