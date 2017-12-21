#pragma once
#include <filesystem>
#include <string>
#include <algorithm>
#include <vector>

namespace filesystem = std::experimental::filesystem::v1;

class Ads {
public:

    static void initialize(filesystem::path pDirectoryContainingAds = "ads", std::string allowedExtension = ".jpg");
    static std::string random();

private:
    static void shuffle();
    static filesystem::path directoryContainingAds;
    static std::vector<std::string> files;

};
