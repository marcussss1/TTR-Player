#pragma once

#include "CurrentPlaylistUIModel.hpp"

class CurrentPlaylistController {
 public:
    explicit CurrentPlaylistController(CurrentPlaylistUIModel* model);

    void addTrack(std::string path);
    void deleteTrack(int index);
    void chooseTrack(int index);
 private:
    CurrentPlaylistUIModel* model_;
};
