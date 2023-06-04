#include "CurrentTrackView.hpp"


const int CURRENT_TRACK_WIDGET_X = 150 - 125;
const int SHUFFLE_BUTTON_X = 325 - 70 - 125;
const int PREVIOUS_TRACK_BUTTON_X = 370 - 70 - 125;
const int PLAY_BUTTON_X = 415 - 70 - 125;
const int NEXT_TRACK_BUTTON_X = 480 - 70 - 125;
const int REPEAT_BUTTON_X = 525 - 70 - 125;
const int MUTE_BUTTON_X = 605 - 110;
const int VOLUME_SLIDER_X = 655 - 110;
const int DURATION_SLIDER_X = 250 - 70 - 110;
const int CURRENT_TRACK_TITLE = 1;

//////////////////////////////////////// Coordinats y ////////////////////////////////////////

const int CURRENT_TRACK_WIDGET_Y = 450;
const int BUTTON_Y = 535;
const int PLAY_BUTTON_Y = 525;
const int DURATION_SLIDER_Y = 485;

//////////////////////////////////////// Widths ////////////////////////////////////////

const int CURRENT_TRACK_WIDGET_WIDTH = 650;
const int BUTTON_WIDTH = 35;
const int PLAY_BUTTON_WIDTH = 50;
const int VOLUME_SLIDER_WIDTH = 125;
const int DURATION_SLIDER_WIDTH = 400;

//////////////////////////////////////// Heights ////////////////////////////////////////

const int CURRENT_TRACK_WIDGET_HEIGHT = 275;
const int BUTTON_HEIGHT = 35;
const int PLAY_BUTTON_HEIGHT = 50;

//////////////////////////////////////// Names ////////////////////////////////////////

const char* CURRENT_TRACK_WIDGET_NAME = "currentTrackWidget";
const char* SHUFFLE_NAME = "shuffle";
const char* PREVIOUS_TRACK_NAME = "previousTrack";
const char* PLAY_NAME = "play";
const char* NEXT_TRACK_NAME = "nextTrack";
const char* REPEAT_NAME = "Off";
const char* MUTE_NAME = "Off";
const char* VOLUME_SLIDER_NAME = "volumeSlider";
const char* DURATION_SLIDER_NAME = "durationSlider";

//////////////////////////////////////// Current Track View ////////////////////////////////////////

CurrentTrackView::CurrentTrackView(CurrentTrackUIModel* model, QWidget* parent)
    : currentTracksCount_(0),
      model_(model),
      controller_(new CurrentTrackController(model)),
      parent_(parent),
      currentTrackWidget_(new QWidget(parent)),
      play_(new QPushButton(parent)),
      repeat_(new QPushButton(parent)),
      mute_(new QPushButton(parent)),
      volumeSliderAll_(new QSlider(Qt::Horizontal, parent)),
      currentTrackTitle_(new QLabel(parent)),
      currentTracksNumbers_(10, nullptr),
      playButtons_(10, nullptr),
      muteButtons_(10, nullptr),
      repeatButtons_(10, nullptr),
      durationSlider_(10, nullptr),
      trackNames_(10, nullptr),
      paths_(10),
      volumeSlider_(10, nullptr),
      playTracks_(10, nullptr),
      durationsBegin_(10),
      durationsEnd_(10) {

    for (size_t i = 0; i < 10; ++i) {
        currentTracksNumbers_[i] = new QPushButton(parent);
        playButtons_[i] = new QPushButton(parent);
        muteButtons_[i] = new QPushButton(parent);
        repeatButtons_[i] = new QPushButton(parent);
        durationSlider_[i] = new QSlider(Qt::Horizontal, parent);
        volumeSlider_[i] = new QSlider(Qt::Horizontal, parent);
        trackNames_[i] = new QLabel(parent);
    }

    connect(play_, SIGNAL(clicked()),
            this, SLOT(playAll()));

    connect(repeat_, SIGNAL(clicked()),
            this, SLOT(repeatAll()));

    connect(mute_, SIGNAL(clicked()),
            this, SLOT(muteAll()));

    connect(volumeSliderAll_, SIGNAL(valueChanged(int)),
            this, SLOT(setVolumeAll(int)));

    setStyle(CURRENT_TRACK_WIDGET_X - 200, CURRENT_TRACK_WIDGET_Y,
             CURRENT_TRACK_WIDGET_WIDTH + 200, CURRENT_TRACK_WIDGET_HEIGHT,
             CURRENT_TRACK_WIDGET_NAME, currentTrackWidget_);

    setStyle(MUTE_BUTTON_X - 240, PLAY_BUTTON_Y,
             PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT,
             PLAY_NAME, play_);

    setStyle(MUTE_BUTTON_X - 180, BUTTON_Y,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             REPEAT_NAME, repeat_); 

    setStyle(MUTE_BUTTON_X - 180 + 50, BUTTON_Y,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             MUTE_NAME, mute_);

    setStyle(MUTE_BUTTON_X - 180 + 90, BUTTON_Y,
             VOLUME_SLIDER_WIDTH, BUTTON_HEIGHT,
             MUTE_NAME, volumeSliderAll_);

    play_->setObjectName("play");
    play_->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/play.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/playFocus.png); }");

    repeat_->setObjectName("Off");
    repeat_->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeat.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeatFocus.png); }");

    mute_->setObjectName("Off");
    mute_->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOff.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOffFocus.png); }");

    currentTrackTitle_->setText("Текущий трек:");
    volumeSliderAll_->setValue(50);
}

void CurrentTrackView::setStyle(int buttonX, int buttonY,
                                int buttonWidth, int buttonHeight,
                                const char* buttonName, QWidget* object) {
    object->setObjectName(buttonName);
    object->setGeometry(QRect(buttonX, buttonY,
                              buttonWidth, buttonHeight));
}

void CurrentTrackView::repeatAll() {
    if (repeat_->objectName()[1] == "f") {
        for (size_t i = 0; i < playTracks_.size(); ++i) {
            if (playTracks_[i] != nullptr) {
                emit repeatButtons_[i]->clicked();
            }
            if (playTracks_[i] != nullptr && !playTracks_[i]->isRepeating()) {
                emit repeatButtons_[i]->clicked();
            }
        }
        std::string string = "On";
        QString a = string.c_str();
        repeat_->setObjectName(a);
        repeat_->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeatFocus.png); }");
    } else {
        for (size_t i = 0; i < playTracks_.size(); ++i) {
            if (playTracks_[i] != nullptr) {
                emit repeatButtons_[i]->clicked();
            }
            if (playTracks_[i] != nullptr && playTracks_[i]->isRepeating()) {
                emit repeatButtons_[i]->clicked();
            }
        }
        std::string string = "Off";
        QString a = string.c_str();
        repeat_->setObjectName(a);
        repeat_->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeat.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeatFocus.png); }");
    }
}

void CurrentTrackView::muteAll() {
    if (mute_->objectName()[1] == "f") {
        for (size_t i = 0; i < playTracks_.size(); ++i) {
            if (playTracks_[i] != nullptr) {
                emit muteButtons_[i]->clicked();
            }
            if (playTracks_[i] != nullptr && !playTracks_[i]->isMuting()) {
                emit muteButtons_[i]->clicked();
            }
        }
        std::string string = "On";
        QString a = string.c_str();
        mute_->setObjectName(a);
        mute_->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOn.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOnFocus.png); }");
    } else {
        for (size_t i = 0; i < playTracks_.size(); ++i) {
            if (playTracks_[i] != nullptr) {
                emit muteButtons_[i]->clicked();
            }
            if (playTracks_[i] != nullptr && playTracks_[i]->isMuting()) {
                emit muteButtons_[i]->clicked();
            }
        }
        std::string string = "Off";
        QString a = string.c_str();
        mute_->setObjectName(a);
        mute_->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOff.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOffFocus.png); }");
    }
}

void CurrentTrackView::setVolumeAll(int position) {
    for (size_t i = 0; i < playTracks_.size(); ++i) {
        if (playTracks_[i] != nullptr) {
            emit volumeSlider_[i]->valueChanged(position);
        }
    }
}

#include "QTrack.hpp"
#include <Track.hpp>

void CurrentTrackView::currentTrackChanged(QString path, int index, bool flag) {

    connect(playButtons_[currentTracksCount_], SIGNAL(clicked()),
            this, SLOT(play()));

    connect(muteButtons_[currentTracksCount_], SIGNAL(clicked()),
            this, SLOT(mute()));

    connect(repeatButtons_[currentTracksCount_], SIGNAL(clicked()),
            this, SLOT(repeat()));

    connect(volumeSlider_[currentTracksCount_], SIGNAL(valueChanged(int)),
            this, SLOT(setVolume(int)));

    connect(durationSlider_[currentTracksCount_], SIGNAL(valueChanged(int)),
            this, SLOT(setDuration(int)));

    currentTracksNumbers_[currentTracksCount_]->setObjectName("On" + QString(currentTracksCount_));
    currentTracksNumbers_[currentTracksCount_]->setStyleSheet("QPushButton { border: solid; border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/otrezok.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/otrezokFocus.png); }");

    std::string on = "On" + std::to_string(currentTracksCount_ + 1);
    std::string off = "Off" + std::to_string(currentTracksCount_ + 1);

    const char* On = &on[0];
    const char* Off = &off[0];

    if (flag) {
        auto qtrack = new QTrack;
        qtrack->setCurrentTrack(path);
        auto track = new Track(qtrack);

        auto string = path.toStdString();
        std::reverse(string.begin(), string.end());
        
        string = string.substr(string.find('.') + 1);
        string = string.substr(0, string.find('/'));
        
        std::reverse(string.begin(), string.end());

        track->setData(path.toStdString(),
                       string.substr(0, string.find('-')),
                       string.substr(string.find('-') + 1));

        playTracks_[currentTracksCount_] = track;
        playTracks_[currentTracksCount_]->track_->mplayer()->setObjectName(On);

        connect(playTracks_[currentTracksCount_]->track_->mplayer(), SIGNAL(positionChanged(qint64)), this, SLOT(elapsedTime(qint64)));
        connect(playTracks_[currentTracksCount_]->track_->mplayer(), SIGNAL(durationChanged(qint64)), this, SLOT(remaningTime(qint64)));
    }

    trackNames_[currentTracksCount_]->setText(QString::fromStdString(playTracks_[currentTracksCount_]->getData()));
    paths_[currentTracksCount_] = path;

    setStyle(CURRENT_TRACK_WIDGET_X - 200, CURRENT_TRACK_WIDGET_Y - 40 * currentTracksCount_,
             CURRENT_TRACK_WIDGET_WIDTH + 200, CURRENT_TRACK_WIDGET_HEIGHT + 40 * currentTracksCount_,
             CURRENT_TRACK_WIDGET_NAME, currentTrackWidget_);

    setStyle(5, DURATION_SLIDER_Y - 40 * currentTracksCount_,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             On, currentTracksNumbers_[currentTracksCount_]);

    setStyle(MUTE_BUTTON_X - 90, DURATION_SLIDER_Y - 40 * currentTracksCount_,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             Off, playButtons_[currentTracksCount_]);

    setStyle(MUTE_BUTTON_X + 10, DURATION_SLIDER_Y - 40 * currentTracksCount_,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             Off, muteButtons_[currentTracksCount_]);

    setStyle(MUTE_BUTTON_X - 40, DURATION_SLIDER_Y - 40 * currentTracksCount_,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             Off, repeatButtons_[currentTracksCount_]);

    setStyle(DURATION_SLIDER_X - 20, DURATION_SLIDER_Y - 40 * currentTracksCount_,
             DURATION_SLIDER_WIDTH - 50, BUTTON_HEIGHT,
             On, durationSlider_[currentTracksCount_]);

    setStyle(VOLUME_SLIDER_X, DURATION_SLIDER_Y - 40 * currentTracksCount_,
             VOLUME_SLIDER_WIDTH, BUTTON_HEIGHT,
             On, volumeSlider_[currentTracksCount_]);

    setStyle(DURATION_SLIDER_X - 20, DURATION_SLIDER_Y - 20 - 37 * currentTracksCount_,
             DURATION_SLIDER_WIDTH - 50, BUTTON_HEIGHT,
             On, trackNames_[currentTracksCount_]);

    playButtons_[currentTracksCount_]->setObjectName(Off);
    playButtons_[currentTracksCount_]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/play.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/playFocus.png); }");

    muteButtons_[currentTracksCount_]->setObjectName(Off);
    muteButtons_[currentTracksCount_]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOff.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOffFocus.png); }");

    repeatButtons_[currentTracksCount_]->setObjectName(Off);
    repeatButtons_[currentTracksCount_]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeat.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeatFocus.png); }");

    volumeSlider_[currentTracksCount_]->setValue(50);

    auto durationBegin = QInputDialog::getText(nullptr, tr(""),
                                           tr("Начало проигрывания(в секундах)"));
    auto durationBeginInt = durationBegin.toInt();
    durationSlider_[currentTracksCount_]->setValue(durationBeginInt * 1000);
    playTracks_[currentTracksCount_]->setDuration(durationBeginInt * 1000);

    connect(currentTracksNumbers_[currentTracksCount_], SIGNAL(clicked()),
            this, SLOT(numberCurrentTrackClicked()));

    ++currentTracksCount_;
}

#include <fstream>
#include <iostream>

void CurrentTrackView::saveData() {
    std::ofstream outfile("/home/marcussss1/2022_2_MidnightSun/newPlayer.txt");
    for (size_t i = 0; i < playTracks_.size(); ++i) {
        if (playTracks_[i]) {
            outfile << paths_[i].toStdString() << "\n";
            outfile << std::to_string(durationsBegin_[i]) << "\n";
            outfile << std::to_string(durationsEnd_[i]) << "\n";
            outfile << std::to_string(int(playTracks_[i]->isRepeating())) << "\n";
            outfile << std::to_string(volumeSlider_[i]->value()) << "\n";
        }
    }
    outfile << "\n";
    outfile.close();
}

void CurrentTrackView::addTrack(QString path, int beginDuration, int endDuration, int isRepeating, int volume) {

    connect(playButtons_[currentTracksCount_], SIGNAL(clicked()),
            this, SLOT(play()));

    connect(muteButtons_[currentTracksCount_], SIGNAL(clicked()),
            this, SLOT(mute()));

    connect(repeatButtons_[currentTracksCount_], SIGNAL(clicked()),
            this, SLOT(repeat()));

    connect(volumeSlider_[currentTracksCount_], SIGNAL(valueChanged(int)),
            this, SLOT(setVolume(int)));

    connect(durationSlider_[currentTracksCount_], SIGNAL(valueChanged(int)),
            this, SLOT(setDuration(int)));

    currentTracksNumbers_[currentTracksCount_]->setObjectName("On" + QString(currentTracksCount_));
    currentTracksNumbers_[currentTracksCount_]->setStyleSheet("QPushButton { border: solid; border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/otrezok.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/otrezokFocus.png); }");

    std::string on = "On" + std::to_string(currentTracksCount_ + 1);
    std::string off = "Off" + std::to_string(currentTracksCount_ + 1);

    const char* On = &on[0];
    const char* Off = &off[0];

    auto qtrack = new QTrack;
    qtrack->setCurrentTrack(path);
    auto track = new Track(qtrack);

    auto string = path.toStdString();
    std::reverse(string.begin(), string.end());
    
    string = string.substr(string.find('.') + 1);
    string = string.substr(0, string.find('/'));
    
    std::reverse(string.begin(), string.end());

    track->setData(path.toStdString(),
                    string.substr(0, string.find('-')),
                    string.substr(string.find('-') + 1));

    playTracks_[currentTracksCount_] = track;
    playTracks_[currentTracksCount_]->track_->mplayer()->setObjectName(On);

    connect(playTracks_[currentTracksCount_]->track_->mplayer(), SIGNAL(positionChanged(qint64)), this, SLOT(elapsedTime(qint64)));
    connect(playTracks_[currentTracksCount_]->track_->mplayer(), SIGNAL(durationChanged(qint64)), this, SLOT(remaningTime(qint64)));

    trackNames_[currentTracksCount_]->setText(QString::fromStdString(playTracks_[currentTracksCount_]->getData()));

    setStyle(CURRENT_TRACK_WIDGET_X - 200, CURRENT_TRACK_WIDGET_Y - 40 * currentTracksCount_,
             CURRENT_TRACK_WIDGET_WIDTH + 200, CURRENT_TRACK_WIDGET_HEIGHT + 40 * currentTracksCount_,
             CURRENT_TRACK_WIDGET_NAME, currentTrackWidget_);

    setStyle(5, DURATION_SLIDER_Y - 40 * currentTracksCount_,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             On, currentTracksNumbers_[currentTracksCount_]);

    setStyle(MUTE_BUTTON_X - 90, DURATION_SLIDER_Y - 40 * currentTracksCount_,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             Off, playButtons_[currentTracksCount_]);

    setStyle(MUTE_BUTTON_X + 10, DURATION_SLIDER_Y - 40 * currentTracksCount_,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             Off, muteButtons_[currentTracksCount_]);

    setStyle(MUTE_BUTTON_X - 40, DURATION_SLIDER_Y - 40 * currentTracksCount_,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             Off, repeatButtons_[currentTracksCount_]);

    setStyle(DURATION_SLIDER_X - 20, DURATION_SLIDER_Y - 40 * currentTracksCount_,
             DURATION_SLIDER_WIDTH - 50, BUTTON_HEIGHT,
             On, durationSlider_[currentTracksCount_]);

    setStyle(VOLUME_SLIDER_X, DURATION_SLIDER_Y - 40 * currentTracksCount_,
             VOLUME_SLIDER_WIDTH, BUTTON_HEIGHT,
             On, volumeSlider_[currentTracksCount_]);

    setStyle(DURATION_SLIDER_X - 20, DURATION_SLIDER_Y - 20 - 37 * currentTracksCount_,
             DURATION_SLIDER_WIDTH - 50, BUTTON_HEIGHT,
             On, trackNames_[currentTracksCount_]);

    playButtons_[currentTracksCount_]->setObjectName(Off);
    playButtons_[currentTracksCount_]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/play.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/playFocus.png); }");

    muteButtons_[currentTracksCount_]->setObjectName(Off);
    muteButtons_[currentTracksCount_]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOff.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOffFocus.png); }");

    volumeSlider_[currentTracksCount_]->setValue(50);

    auto durationBegin = QInputDialog::getText(nullptr, tr(""),
                                           tr("Начало проигрывания(в секундах)"));
    auto durationBeginInt = durationBegin.toInt();
    durationSlider_[currentTracksCount_]->setValue(durationBeginInt * 1000);
    playTracks_[currentTracksCount_]->setDuration(durationBeginInt * 1000);

    connect(currentTracksNumbers_[currentTracksCount_], SIGNAL(clicked()),
            this, SLOT(numberCurrentTrackClicked()));

    durationsBegin_[currentTracksCount_] = beginDuration;
    durationsEnd_[currentTracksCount_] = endDuration;

    playTracks_[currentTracksCount_]->setVolume(volume);
    playTracks_[currentTracksCount_]->setDuration(beginDuration);

    if (isRepeating) {
        playTracks_[currentTracksCount_]->repeat();
        repeatButtons_[currentTracksCount_]->setObjectName(On);
        repeatButtons_[currentTracksCount_]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeatFocus.png); }");
    } else {
        repeatButtons_[currentTracksCount_]->setObjectName(Off);
        repeatButtons_[currentTracksCount_]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeat.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeatFocus.png); }");
    }

    ++currentTracksCount_;
}

void CurrentTrackView::deleteCurrentTrack(QString path, int index) {
    playTracks_[index] = nullptr;

    std::vector<QString> arr;
    
    currentTracksCount_ = 0;
    for (size_t i = 0; i < trackNames_.size(); ++i) {
        if (trackNames_[i] && trackNames_[i]->text() != "" && trackNames_[i]->text() != "Deleted" && trackNames_[i]->text() != path) {
            arr.push_back(trackNames_[i]->text());
        }
    }

    for (size_t i = 0; i < 10; ++i) {
        setStyle(0, 0, 0, 0, "Deleted", currentTracksNumbers_[i]);
        setStyle(0, 0, 0, 0, "Deleted", playButtons_[i]);
        setStyle(0, 0, 0, 0, "Deleted", muteButtons_[i]);
        setStyle(0, 0, 0, 0, "Deleted", repeatButtons_[i]);
        setStyle(0, 0, 0, 0, "Deleted", durationSlider_[i]);
        setStyle(0, 0, 0, 0, "Deleted", volumeSlider_[i]);
        setStyle(0, 0, 0, 0, "Deleted", trackNames_[i]);
    }

    for (size_t i = 0, j = 0; i < playTracks_.size(); ++i) {
        if (playTracks_[i] != nullptr) {
            currentTrackChanged(arr[j], i, false); // не совпадение индеков, в названии истина
            ++j;
        }
    }
}

void CurrentTrackView::elapsedTime(qint64 position) {
    int index = sender()->objectName().toStdString().back() - '0' - 1;
    durationSlider_[index]->setValue(position);
}

void CurrentTrackView::remaningTime(qint64 position) {
    int index = sender()->objectName().toStdString().back() - '0' - 1;
    durationSlider_[index]->setRange(0, position);
    durationsEnd_[index] = position;
}

void CurrentTrackView::currentTrackStatus(int index) {
}

void CurrentTrackView::numberCurrentTrackClicked() {

    auto durationBegin = QInputDialog::getText(nullptr, tr(""),
                                         tr("Начало(в секундах)"));
    auto durationEnd = QInputDialog::getText(nullptr, tr(""),
                                         tr("Конец(в секундах)"));

    auto durationBeginInt = durationBegin.toInt();
    auto durationEndInt = durationEnd.toInt();

    auto index = sender()->objectName().toStdString().back() - '0' - 1;

    durationSlider_[index]->setValue(durationBeginInt * 1000);
    playTracks_[index]->setDuration(durationBeginInt * 1000);

    durationsBegin_[index] = durationBeginInt * 1000;
    durationsEnd_[index] = durationEndInt * 1000;
}

void CurrentTrackView::playAll() {
    if (play_->objectName() == "play") {
        for (size_t i = 0; i < playTracks_.size(); ++i) {
            if (playTracks_[i] != nullptr) {
                emit playButtons_[i]->clicked();
            }
            if (playTracks_[i] != nullptr && !playTracks_[i]->isPlaying()) {
                emit playButtons_[i]->clicked();
            }
        }
        play_->setObjectName("pause");
        play_->setStyleSheet("QPushButton#pause { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/pause.png); } QPushButton:hover#pause { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/pauseFocus.png); }");
    } else {
        for (size_t i = 0; i < playTracks_.size(); ++i) {
            if (playTracks_[i] != nullptr) {
                emit playButtons_[i]->clicked();
            }
            if (playTracks_[i] != nullptr && playTracks_[i]->isPlaying()) {
                emit playButtons_[i]->clicked();
            }
        }
        play_->setObjectName("play");
        play_->setStyleSheet("QPushButton#play { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/play.png); } QPushButton:hover#play { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/playFocus.png); }");
    }
}

void CurrentTrackView::play() {
    int index = sender()->objectName().toStdString().back() - '0' - 1;
    if (playButtons_[index]->objectName()[1] == "f") {
        playTracks_[index]->play();
        std::string string = "On" + std::to_string(index + 1);
        QString a = string.c_str();
        playButtons_[index]->setObjectName(a);
        playButtons_[index]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/pause.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/pauseFocus.png); }");
    } else {
        playTracks_[index]->pause();
        std::string string = "Off" + std::to_string(index + 1);
        QString a = string.c_str();
        playButtons_[index]->setObjectName(a);
        playButtons_[index]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/play.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/playFocus.png); }");
    }
}

void CurrentTrackView::repeat() {
    int index = sender()->objectName().toStdString().back() - '0' - 1;
    playTracks_[index]->repeat();
    if (repeatButtons_[index]->objectName()[1] == "f") {
        std::string string = "On" + std::to_string(index + 1);
        QString a = string.c_str();
        repeatButtons_[index]->setObjectName(a);
        repeatButtons_[index]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeatFocus.png); }");
    } else {
        std::string string = "Off" + std::to_string(index + 1);
        QString a = string.c_str();
        repeatButtons_[index]->setObjectName(a);
        repeatButtons_[index]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeat.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/repeatFocus.png); }");
    }
}

void CurrentTrackView::mute() {
    int index = sender()->objectName().toStdString().back() - '0' - 1;
    if (muteButtons_[index]->objectName()[1] == "f") {
        playTracks_[index]->mute();
        std::string string = "On" + std::to_string(index + 1);
        QString a = string.c_str();
        muteButtons_[index]->setObjectName(a);
        muteButtons_[index]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOn.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOnFocus.png); }");
    } else {
        playTracks_[index]->mute();
        std::string string = "Off" + std::to_string(index + 1);
        QString a = string.c_str();
        muteButtons_[index]->setObjectName(a);
        muteButtons_[index]->setStyleSheet("QPushButton { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOff.png); } QPushButton:hover { border-image: url(/home/marcussss1/2022_2_MidnightSun/project/impl/icons/muteOffFocus.png); }");
    }
}

void CurrentTrackView::setDuration(int position) {
    int index = sender()->objectName().toStdString().back() - '0' - 1;
    if (playTracks_[index]->isRepeating() && durationsEnd_[index] - position < 1000) {
        if (durationsBegin_[index] - 1000 < 0) {
            playTracks_[index]->setDuration(0);
        } else {
            playTracks_[index]->setDuration(durationsBegin_[index] - 1000);
        }
        return;
    }

    if (position < durationsEnd_[index]) {
        playTracks_[index]->setDuration(position);
    }
}

void CurrentTrackView::setVolume(int position) {
    int index = sender()->objectName().toStdString().back() - '0' - 1;
    playTracks_[index]->setVolume(position);
    volumeSlider_[index]->setValue(position);
}


void CurrentTrackView::shuffle() {
    controller_->shuffle();
}

void CurrentTrackView::previousTrack() {
    controller_->previousTrack();
}

void CurrentTrackView::nextTrack() {
    controller_->nextTrack();
}

void CurrentTrackView::setCurrentTrackMediator(Mediator* mediator) {
    model_->setCurrentTrackMediator(mediator);
}

CurrentTrackUIModel* CurrentTrackView::getModel() {
    return model_;
}
