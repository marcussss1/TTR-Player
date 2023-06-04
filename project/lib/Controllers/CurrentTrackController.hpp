#pragma once

#include "CurrentTrackUIModel.hpp"

class CurrentTrackController {
 public:
    explicit CurrentTrackController(CurrentTrackUIModel* model);

    void play(int index);
    void pause(int index);
    void stop(int index);
    void repeat(int index);
    void mute(int index);
    void setDuration(int index, int position);
    void setVolume(int index, int position);

    void shuffle();
    void previousTrack();
    void nextTrack();
 private: 
    CurrentTrackUIModel* model_;  
};
