#pragma once

#include "CurrentPlaylistController.hpp"

#include <QAction>
#include <QMenu>
#include <QHeaderView>
#include <QTableWidget>

class CurrentPlaylistView : public QTableWidget {
 Q_OBJECT
 public:
    explicit CurrentPlaylistView(CurrentPlaylistUIModel* model, QWidget* parent);
    ~CurrentPlaylistView() = default;

    void setCurrentPlaylistMediator(Mediator* mediator);
    CurrentPlaylistUIModel* getModel();

 signals:
    void currentTrackChanged(QString, int, bool);
    void deleteCurrentTrack(QString, int);

 private slots:
    void trackClicked();
   
    void addTrackInWidget(QString path, bool flag); // триггерится другой вьюшкой
                                         // может также триггерится моим экшеном
    void chooseTrackInWidget();

    void removeCurrentTrack();

 private:
    size_t currentTracksCount_;
   
    CurrentPlaylistUIModel* model_;
    CurrentPlaylistController* controller_;
    
    QTableWidget* currentPlaylistWidget_;
    QMenu* menu_;
    QAction* addTrack_;
    QAction* deleteTrack_;
    QAction* chooseTrack_;
};
