#pragma once

#include "Mediator.hpp"
#include "Playlist.hpp"

class CurrentPlaylistUIModel : public Sender {
 public:
    void setCurrentPlaylistMediator(Mediator* mediator);

    void addTrack(std::string path);
    void deleteTrack(int index);
    void chooseTrack(int index);

    void shuffle();
    void previousTrack();
    void nextTrack();

 private:
    Playlist playlist_;
};
