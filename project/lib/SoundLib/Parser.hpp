#pragma once

#include "QTrack.hpp"
#include "Track.hpp"
#include <experimental/filesystem>

class Parser {
 public:
    Track* parsingPath(std::string path);
 
 private:
    bool isFileExist(std::string path);
    bool isAudioFile(std::string path);
};
