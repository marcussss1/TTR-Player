#include "CurrentPlaylistController.hpp"

CurrentPlaylistController::CurrentPlaylistController(CurrentPlaylistUIModel* model)
    : model_(model) {}

void CurrentPlaylistController::addTrack(std::string path) {
    model_->addTrack(path);
}

void CurrentPlaylistController::deleteTrack(int index) {
    model_->deleteTrack(index);
}

void CurrentPlaylistController::chooseTrack(int index) {
    model_->chooseTrack(index);
}
