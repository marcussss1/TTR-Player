#pragma once

#include <QMainWindow>
#include <QFile>
#include <QApplication>
#include <QtGui/QMouseEvent>

#include "CurrentPlaylistView.hpp"
#include "CurrentTrackView.hpp"
#include "FileSystemView.hpp"
#include "LeftWallView.hpp"
#include "TitleBarButtonsView.hpp"
#include "GlobalModel.hpp"

class MainWindowWidget : public QWidget {
 Q_OBJECT
 public:
    explicit MainWindowWidget(QWidget* parent = nullptr);
    ~MainWindowWidget() = default;
  protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
  private:
    QPoint oldPos;
};

class MainView : public QObject {
  Q_OBJECT
  public:
    MainView();
    ~MainView() = default;

    void show();
    void close();
  private:
    TrackPlaylistModel* mediator_;
    MainWindowWidget mainWindowWidget_;
    TitleBarButtonsWidget titleBarButtonsWidget_;

    CurrentTrackView currentTrackView_;
    CurrentPlaylistView currentPlaylistView_;
    FileSystemView fileSystemView_;
};
