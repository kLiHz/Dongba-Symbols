#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    std::string root_path;
    std::string id;
    if (argc > 1) {
        root_path = argv[1];
    } else {
        std::cout << "* Please assign the root directory of the folders: ";
        std::cin >> root_path;
    }
    if (argc > 2) {
        id = argv[2];
    } else {
        std::cout << "* Please assign your id: ";
        std::cin >> id;
    }

    if (!fs::exists(root_path)) {
        std::cerr << "Directory \'" << root_path << "\' not found!\n";
        return 0;
    } else if (!fs::is_directory(root_path)) {
        std::cerr << "\'" << root_path << "\' is not a directory!\n";
        return 0;
    } else {
        std::cout << "Root directory is: " << root_path << '\n';
        std::cout << "Files will be renamed as: \n    " 
                  << root_path << "/<subdir>/" << id << "_<subdirname>_<i>.<extension>" 
                  << std::endl;
    }

    for (fs::directory_iterator folder(root_path); folder != fs::end(folder); ++folder) {
        if (fs::is_directory(folder->status())) {
            std::cout << "- Now entering: " << folder->path() << std::endl;
            int i = 0;
            std::string folder_name = folder->path().stem().string();
            for (fs::directory_iterator item(folder->path()); item != fs::end(item); ++item) {
                auto extension = item->path().extension().string();
                ++i;
                fs::rename(item->path(), folder->path()/(id + '_' + folder_name + '_' + std::to_string(i) + extension));
            }
        }
    }
    std::cout << "Finished!" << std::endl;

    return 0;
}
