#pragma once

#include <QMediaPlayer>

class ITrack {
 public:
    virtual ~ITrack() = default;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void mute() = 0;
    virtual void setVolume(int position) = 0;
    virtual void setDuration(int position) = 0;

    virtual QMediaPlayer* mplayer() = 0;
};
