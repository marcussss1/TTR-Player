#include "Playlist.hpp"

void Playlist::addTrack(std::string path) {
    auto track = parser.parsingPath(path);
    if (!track) {
        return;
    }
    tracksList_.push_back(track);
}

void Playlist::chooseTrack(int index) {
    if (index < tracksList_.size()) {
        currentTrack_ = tracksList_[index];
        currentTrackPosition_ = index;
    }
}

void Playlist::deleteTrack(int index) {
    if (index >= tracksList_.size()) {
        return;
    }

    auto deletedTrack = tracksList_[index];
    auto deletedTrackInPlaylist = find(tracksList_.begin(),
                                       tracksList_.end(),
                                       deletedTrack);

    if (deletedTrackInPlaylist != tracksList_.end()) {
        tracksList_.erase(deletedTrackInPlaylist);
    }

    if (deletedTrack == currentTrack_) {
        if (tracksList_.size() != 1) {
            chooseTrack(currentTrackPosition_ - 1);
        } else {
            currentTrack_ = nullptr;
        }
    }
}

void Playlist::previousTrack() {
    if (currentTrackPosition_ != 0) {
        currentTrack_ = tracksList_[--currentTrackPosition_];
    }
}

void Playlist::nextTrack() {
    if (currentTrackPosition_ + 1 == tracksList_.size()) {
        currentTrack_ = tracksList_[0];
        currentTrackPosition_ = 0;
    } else {
        currentTrack_ = tracksList_[++currentTrackPosition_];
    }
}

void Playlist::shuffle() {
    std::shuffle(tracksList_.begin(),
                 tracksList_.end(),
                 std::random_device());
}

Track* Playlist::currentTrack() noexcept {
    return currentTrack_;
}

Track* Playlist::operator[](int index) noexcept {
    return tracksList_[index];
}

int Playlist::size() const noexcept {
    return tracksList_.size();
}
