#include "CurrentTrackUIModel.hpp"

void CurrentTrackUIModel::setCurrentTrackMediator(Mediator* mediator) {
    mediator_ = mediator;
}

void CurrentTrackUIModel::play(int index) {
    if (index < currentTracks_.size() && currentTracks_[index]) {
        currentTracks_[index]->play();
    }
}

void CurrentTrackUIModel::pause(int index) {
    if (index < currentTracks_.size() && currentTracks_[index]) {
        currentTracks_[index]->pause();
    }
}

void CurrentTrackUIModel::stop(int index) {
    if (index < currentTracks_.size() && currentTracks_[index]) {
        currentTracks_[index]->stop();
    }
}

void CurrentTrackUIModel::repeat(int index) {
    if (index < currentTracks_.size() && currentTracks_[index]) {
        currentTracks_[index]->repeat();
    }
}

void CurrentTrackUIModel::mute(int index) {
    if (index < currentTracks_.size() && currentTracks_[index]) {
        currentTracks_[index]->mute();
    }
}

void CurrentTrackUIModel::setDuration(int index, int position) {
    if (index < currentTracks_.size() && currentTracks_[index]) {
        currentTracks_[index]->setDuration(position);
    }
}

void CurrentTrackUIModel::setVolume(int index, int position) {
    if (index < currentTracks_.size() && currentTracks_[index]) {
        currentTracks_[index]->setVolume(position);
    }
}

void CurrentTrackUIModel::chooseTrack(Track* track, bool prevNextTrack) {
}


void CurrentTrackUIModel::shuffle() {
    mediator_->notifyTrackPlaylist(this, Shuffle);
}

void CurrentTrackUIModel::previousTrack() {
    mediator_->notifyTrackPlaylist(this, PreviousTrack, true);
}

void CurrentTrackUIModel::nextTrack() {
    mediator_->notifyTrackPlaylist(this, NextTrack, true);
}
