#include "stdafx.h"
#include "Ads.h"
#include <random>

Ads & Ads::instance()
{
    static Ads singleinstance;
    return singleinstance;
}

void Ads::initialize(filesystem::path pDirectoryContainingAds, std::string allowedExtension)
{
    directoryContainingAds = pDirectoryContainingAds;

    auto entries = filesystem::directory_iterator(directoryContainingAds);

    for (const auto& entry : entries) {
        auto path = entry.path();
        auto type = entry.status().type();

        if (!path.has_filename() || !path.has_extension() || type != filesystem::file_type::regular) continue;

        if (path.extension() == allowedExtension) {
            files.push_back(path.string());
        }

        unUsedFiles = files;
    }
}

std::string Ads::random()
{
    shuffle();
    std::string file = unUsedFiles.front();
    unUsedFiles.erase(unUsedFiles.begin());

    if (unUsedFiles.size() <= 0)
    {
        unUsedFiles = files;
    }

    return file;
}

void Ads::close()
{
    files.~vector();
    unUsedFiles.~vector();
    directoryContainingAds.~path();
}

void Ads::shuffle()
{
    if (unUsedFiles.size() > 0) {
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(unUsedFiles.begin(), unUsedFiles.end(), g);
    }
}
