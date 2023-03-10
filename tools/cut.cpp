#include <iostream>
#include <string>

#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>

int main(int argc, char* argv[]) {
    auto keys =
            "{ help h usage |             | Print this message.           }"
            "{ thickness b  | 1           | Grid line thickness in px.    }"
            "{ length l     | 200         | Length of a side in px.       }"
            "{ cols c       | 4           | Number of squares in a row.   }"
            "{ rows r       | 5           | Rows of squares.              }"
            "{ input i      | grid.png    | Input filename.               }"
            "{ output o     | slice_.png  | Output prefix with extension. }"
    ;

    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Grid Cutter v0.0.1");

    if (parser.has("help")) {
        parser.printMessage();  // Print HELP message
        return 0;               // Then end the program, DO NOTHING
    }

    auto rows = parser.get<int>("rows");
    auto cols = parser.get<int>("cols");
    auto thickness = parser.get<int>("thickness");
    auto lineWidth = 2 * thickness - 1;
    auto length = parser.get<int>("length");
    auto input = parser.get<std::string>("input");
    auto output = parser.get<std::string>("output");

    std::cout << std::boolalpha;
    std::cout << "Rows:                         " << rows << '\n';
    std::cout << "Cols:                         " << cols << '\n';
    std::cout << "Pixel in length:              " << length << " px \n";
    std::cout << "Grid line thickness:          " << thickness << " px \n";
    std::cout << "Grid line width:              " << lineWidth << " px \n";
    std::cout << "Input filename:               " << input << '\n';
    std::cout << "Output:                       " << output << '\n';

    auto p = output.find_last_of(".");
    auto prefix = output.substr(0, p);
    auto extension = output.substr(p);

    std::cout << "Output prefix:                " << prefix << '\n';
    std::cout << "Output extension              " << extension << '\n';
    std::cout << std::noboolalpha;

    if (!parser.check()) {
        parser.printErrors();
        return 0;
    }

    auto canvas = cv::imread(input);

    if (canvas.empty()) {
        std::cerr << "Failed to open input image. \n";
        return 1;
    }

    for (int i = 0; i < rows; i += 1) {
        for (int j = 0; j < cols; j += 1) {
            auto y = (length + lineWidth) * i + lineWidth;
            auto x = (length + lineWidth) * j + lineWidth;
            auto roi = cv::Rect(x, y, length, length);
            auto slice = canvas(roi);
            cv::imwrite(prefix + std::to_string(i * cols + j + 1) + extension, slice);
        }
    }
}
