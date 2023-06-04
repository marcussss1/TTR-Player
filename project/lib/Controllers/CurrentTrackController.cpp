#include "CurrentTrackController.hpp"

CurrentTrackController::CurrentTrackController(CurrentTrackUIModel* model)
    : model_(model) {}

void CurrentTrackController::play(int index) {
    model_->play(index);
}

void CurrentTrackController::pause(int index) {
    model_->pause(index);
}

void CurrentTrackController::stop(int index) {
    model_->stop(index);
}

void CurrentTrackController::repeat(int index) {
    model_->repeat(index);
}

void CurrentTrackController::mute(int index) {
    model_->mute(index);
}

void CurrentTrackController::setDuration(int index, int position) {
    model_->setDuration(index, position);
}

void CurrentTrackController::setVolume(int index, int position) {
    model_->setVolume(index, position);
}


void CurrentTrackController::shuffle() {
    model_->shuffle();
}

void CurrentTrackController::previousTrack() {
    model_->previousTrack();
}

void CurrentTrackController::nextTrack() {
    model_->nextTrack();
}
