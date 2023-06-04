#pragma once

#include "Mediator.hpp"
#include "Track.hpp"

class CurrentTrackUIModel : public Sender {
 public:   
    void setCurrentTrackMediator(Mediator* mediator);

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

    void chooseTrack(Track* track, bool prevNextTrack);

    std::vector<Track*> currentTracks_;
};
