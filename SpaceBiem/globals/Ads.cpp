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
    }
}

std::string Ads::random()
{
    if (files.size() > 0) {
        shuffle();
        return files.front();
    }
}

void Ads::close()
{
    files.~vector();
    directoryContainingAds.~path();
}

void Ads::shuffle()
{
    if (files.size() > 0) {
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(files.begin(), files.end(), g);
    }
}
