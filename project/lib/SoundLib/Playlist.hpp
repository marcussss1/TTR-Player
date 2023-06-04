#pragma once

#include "Parser.hpp"
#include "Track.hpp"

#include <algorithm>
#include <random>

class Playlist {
 public:
    void addTrack(std::string path);
    void deleteTrack(int index);
    void chooseTrack(int index);

    void previousTrack();
    void nextTrack();
    
    void shuffle();

    Track* operator[](int index) noexcept;
    Track* currentTrack() noexcept;
    int size() const noexcept;

 private:
    std::vector<Track*> tracksList_;
    std::string playlistName_ = "";
    int currentTrackPosition_ = 0;
    Track* currentTrack_ = nullptr;
    Parser parser;
};
