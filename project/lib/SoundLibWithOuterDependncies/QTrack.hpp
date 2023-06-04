#pragma once

#include "ITrack.hpp"
#include <QObject>
#include <QMediaPlayer>

class QTrack : public QObject, public ITrack {
 Q_OBJECT
 private slots:
   void duration(qint64 duration);
   void currrentTime(qint64 position);
 public:
    QTrack();
    ~QTrack();

    void setCurrentTrack(const QString& path);
    
    void play() override;
    void pause() override;
    void mute() override;
    void setVolume(int position) override;
    void setDuration(int position) override;

    QMediaPlayer* mplayer() override;
 private:
    QMediaPlayer* mplayer_ = nullptr;

    int qCurrentTime_ = 0;
    int qDuration_ = 0;
};
