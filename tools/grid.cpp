#include <iostream>
#include <string>

#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char* argv[]) {
    auto keys =
            "{ help h usage |             | Print this message.         }"
            "{ display-only |             | Display by 'cv::imshow'.    }"
            "{ thickness    | 1           | Grid line thickness in px.  }"
            "{ length       | 200         | Length of a side in px.     }"
            "{ cols         | 4           | Number of squares in a row. }"
            "{ rows         | 5           | Rows of squares.            }"
            "{ filename     | grid.png    | Output filename.            }"
            "{ fg           | 0   255 0   | Grid line color (RGB).      }"
            "{ bg           | 255 255 255 | Background color (RGB).     }"
            ;

    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Grid Printer v0.0.1");

    if (parser.has("help")) {
        parser.printMessage();  // Print HELP message
        return 0;               // Then end the program, DO NOTHING
    }

    auto rows = parser.get<int>("rows");
    auto cols = parser.get<int>("cols");
    auto thickness = parser.get<int>("thickness");
    auto lineWidth = 2 * thickness - 1;
    auto length = parser.get<int>("length");
    auto fg = parser.get<cv::Scalar>("fg");
    auto bg = parser.get<cv::Scalar>("bg");
    auto filename = parser.get<std::string>("filename");
    auto displayOnly = parser.has("display-only");

    std::cout << std::boolalpha;
    std::cout << "Rows:                     " << rows << '\n';
    std::cout << "Cols:                     " << cols << '\n';
    std::cout << "Pixel in length:          " << length << " px \n";
    std::cout << "Grid line thickness:      " << thickness << " px \n";
    std::cout << "Grid line width:          " << lineWidth << " px \n";
    std::cout << "Grid line color (RGB):    " << cv::Vec<int, 3>(fg[0], fg[1], fg[2]) << '\n';
    std::cout << "Background color (RGB):   " << cv::Vec<int, 3>(bg[0], bg[1], bg[2]) << '\n';
    std::cout << "Display Only:             " << displayOnly << "\n";
    std::cout << "Output filename:          " << filename << '\n';
    std::cout << std::noboolalpha;

    if (!parser.check()) {
        parser.printErrors();
        return 0;
    }

    auto color = cv::Vec<int, 3>(fg[2], fg[1], fg[0]);
    auto background = cv::Vec<int, 3>(bg[2], bg[1], bg[0]);

    auto height = rows * length + (rows + 1) * lineWidth;
    auto width = cols * length + (cols + 1) * lineWidth;

    auto canvas = cv::Mat(cv::Size(width, height), CV_8UC3, background);

    for (int i = 0; i <= rows; i += 1) {
        auto y = (length + lineWidth) * i + thickness - 1;
        cv::line(canvas, {0, y}, {width, y}, color, thickness);
    }

    for (int i = 0; i <= cols; i += 1) {
        auto x = (length + lineWidth) * i + thickness - 1;
        cv::line(canvas, {x, 0}, {x, height}, color, thickness);
    }

    if (displayOnly) {
        cv::namedWindow("test", cv::WindowFlags::WINDOW_NORMAL);
        cv::imshow("test", canvas);
        cv::waitKey(0);
    } else {
        cv::imwrite(filename, canvas);
    }
}
