#pragma once

#include "CurrentTrackController.hpp"

#include <algorithm>
#include <unordered_map>

#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

class CurrentTrackView : public QObject {
 Q_OBJECT
 public:
    CurrentTrackView(CurrentTrackUIModel* model, QWidget* parent = nullptr);
    ~CurrentTrackView() = default;

    void setCurrentTrackMediator(Mediator* mediator);
    CurrentTrackUIModel* getModel();

 private slots:
    void currentTrackChanged(QString path, int index, bool flag);
    void deleteCurrentTrack(QString path, int index);

    void numberCurrentTrackClicked();

    void saveData();

    void elapsedTime(qint64 position);
    void remaningTime(qint64 position);

 private slots:
    void play();
    void repeat();
    void mute();
    void setDuration(int position);
    void setVolume(int position);

    void shuffle();
    void previousTrack();
    void nextTrack();

    void playAll();
    void repeatAll();
    void muteAll();
    void setVolumeAll(int);

    void addTrack(QString, int, int, int, int);

 signals:
    void removeCurrentTrack();

 public:
   void setStyle(int buttonX, int buttonY,
                 int buttonWidth, int buttonHeight,
                 const char* buttonName, QWidget* object);
 private:
  
    void currentTrackStatus(int index);

    int currentTracksCount_;
 
    CurrentTrackUIModel* model_;
    CurrentTrackController* controller_;
    
    QWidget* parent_;
    QWidget* currentTrackWidget_;
    QPushButton* play_;
    QPushButton* repeat_;
    QPushButton* mute_;
    QSlider* volumeSliderAll_;

    QLabel* currentTrackTitle_;

    std::vector<QPushButton*> currentTracksNumbers_;
    std::vector<QPushButton*> playButtons_;
    std::vector<QPushButton*> muteButtons_;
    std::vector<QPushButton*> repeatButtons_;
    std::vector<QSlider*> durationSlider_;
    std::vector<QSlider*> volumeSlider_;
   
    std::vector<QLabel*> trackNames_;
    std::vector<QString> paths_; 

    std::vector<Track*> playTracks_;

    std::vector<int> durationsBegin_;
    std::vector<int> durationsEnd_;
};
