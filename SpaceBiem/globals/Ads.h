#pragma once
#include <filesystem>
#include <string>
#include <algorithm>
#include <vector>

namespace filesystem = std::experimental::filesystem::v1;

class Ads {
public:

    static Ads& instance();

    void initialize(filesystem::path pDirectoryContainingAds = "ads", std::string allowedExtension = ".jpg");
    std::string random();
    
    void close();
private:
    Ads() {};

    void shuffle();
    filesystem::path directoryContainingAds;
    std::vector<std::string> files;
    std::vector<std::string> unUsedFiles;
 
};
