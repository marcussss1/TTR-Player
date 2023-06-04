#include "QTrack.hpp"

QTrack::QTrack() {
    mplayer_ = new QMediaPlayer;

    connect(mplayer_, SIGNAL(durationChanged(qint64)), 
            this, SLOT(duration(qint64)));

    connect(mplayer_, SIGNAL(positionChanged(qint64)), 
            this, SLOT(currrentTime(qint64)));
}

void QTrack::duration(qint64 duration) {
    qDuration_ = duration;
}

void QTrack::currrentTime(qint64 position) {
    qCurrentTime_ = position;
}

QTrack::~QTrack() {
    delete mplayer_;
}

void QTrack::setCurrentTrack(const QString& path) {
    mplayer_->setMedia(QUrl::fromLocalFile(path));
}

void QTrack::play() {
    mplayer_->play();
}

void QTrack::pause() {
    mplayer_->pause();
}

void QTrack::mute() {
    if (mplayer_->isMuted()) {
        mplayer_->setMuted(false);
    } else {
        mplayer_->setMuted(true);
    }
}

void QTrack::setVolume(int position) {
    mplayer_->setVolume(position);
}

void QTrack::setDuration(int position) {
    mplayer_->setPosition(position);
}

QMediaPlayer* QTrack::mplayer() {
    return mplayer_;
}
