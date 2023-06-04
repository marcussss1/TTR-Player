#include "CurrentPlaylistUIModel.hpp"

void CurrentPlaylistUIModel::setCurrentPlaylistMediator(Mediator* mediator) {
    mediator_ = mediator;
}

void CurrentPlaylistUIModel::addTrack(std::string path) {
    playlist_.addTrack(path);
    if (playlist_.size() == 1) {
        chooseTrack(0);
    }
}

void CurrentPlaylistUIModel::deleteTrack(int index) {
    bool flag = false;
    if (playlist_[index] == playlist_.currentTrack()) {
        flag = true;
    }
    playlist_.deleteTrack(index);
    if (flag) {
        mediator_->notifyTrackPlaylist(this, DeletedTrackIsCurrent, false, playlist_.currentTrack());
    }
}

void CurrentPlaylistUIModel::chooseTrack(int index) {
    playlist_.chooseTrack(index);
    mediator_->notifyTrackPlaylist(this, NewCurrentTrack, false, playlist_.currentTrack());
}


void CurrentPlaylistUIModel::shuffle() {
    playlist_.shuffle();
}

void CurrentPlaylistUIModel::previousTrack() {
    playlist_.previousTrack();
    mediator_->notifyTrackPlaylist(this, NewCurrentTrack, true, playlist_.currentTrack());
}

void CurrentPlaylistUIModel::nextTrack() {
    playlist_.nextTrack();
    mediator_->notifyTrackPlaylist(this, NewCurrentTrack, true, playlist_.currentTrack());
}
