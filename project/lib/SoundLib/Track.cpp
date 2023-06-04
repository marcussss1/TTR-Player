#include "Track.hpp"

Track::Track(ITrack* track) 
    : track_(track) {}

void Track::setData(std::string path,
                    std::string singer,
                    std::string trackName) {
    path_ = path;
    singer_ = singer;
    trackName_ = trackName;
}

void Track::play() noexcept {
    if (!isPlaying_) {
        isPlaying_ = true;
        track_->play();
    }
}

void Track::pause() noexcept {
    if (isPlaying_) {
        isPlaying_ = false;
        track_->pause();
    }
}

void Track::stop() noexcept {
    isPlaying_ = false;
    currentTime_ = 0;
    track_->pause();
    track_->setDuration(0);
}

void Track::repeat() noexcept {
    if (isRepeating_) {
        isRepeating_ = false;
    } else {
        isRepeating_ = true;
    }
}

void Track::mute() noexcept {
    if (isMuting_) {
        isMuting_ = false;
    } else {
        isMuting_ = true;
    }
    track_->mute();
}

void Track::setDuration(int position) noexcept {
    if (position > duration_) {
        currentTime_ = duration_;
    } else {
        currentTime_ = position;
    }
    track_->setDuration(position); // TODO
}

void Track::setVolume(int position) noexcept {
    if (position > 100) {
        volume_ = 100;
    } else {
        volume_ = position;
    }
    track_->setVolume(volume_);
}

bool Track::isPlaying() const noexcept {
    return isPlaying_;
}

bool Track::isRepeating() const noexcept {
    return isRepeating_;
}

bool Track::isMuting() const noexcept {
    return isMuting_;
}
