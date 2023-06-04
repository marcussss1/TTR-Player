#include "MainWindowView.hpp"

#include <QBoxLayout>
#include <QPushButton>
#include <QStyle>

const int MAIN_WINDOW_WIDTH = 800 - 125;
const int MAIN_WINDOW_HEIGHT = 600;

MainWindowWidget::MainWindowWidget(QWidget* parent)
    : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    QFile styleF;
    styleF.setFileName("/home/marcussss1/2022_2_MidnightSun/project/impl/style/style.css");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();
    qApp->setStyleSheet(qssStr);
    setGeometry(QRect(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT));
}

void MainWindowWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        oldPos = event->pos();
    }
}

void MainWindowWidget::mouseMoveEvent(QMouseEvent *event) {
    QPoint delta = event->pos() - oldPos;
    move(pos() + delta);
}

MainView::MainView()
    : mediator_(new TrackPlaylistModel),
      mainWindowWidget_(nullptr),
      titleBarButtonsWidget_(&mainWindowWidget_),
      currentTrackView_(new CurrentTrackUIModel, &mainWindowWidget_),
      currentPlaylistView_(new CurrentPlaylistUIModel, &mainWindowWidget_),
      fileSystemView_(&mainWindowWidget_) {

    connect(&currentPlaylistView_, SIGNAL(currentTrackChanged(QString, int, bool)),
            &currentTrackView_, SLOT(currentTrackChanged(QString, int, bool)));

    connect(&fileSystemView_, SIGNAL(addTrack(QString, int, int, int, int)),
            &currentTrackView_, SLOT(addTrack(QString, int, int, int, int)));

    connect(&currentPlaylistView_, SIGNAL(deleteCurrentTrack(QString, int)),
            &currentTrackView_, SLOT(deleteCurrentTrack(QString, int)));

    connect(&fileSystemView_, SIGNAL(openFile(QString, bool)),
            &currentPlaylistView_, SLOT(addTrackInWidget(QString, bool)));

    connect(&currentTrackView_, SIGNAL(removeCurrentTrack()),
            &currentPlaylistView_, SLOT(removeCurrentTrack()));

    connect(&fileSystemView_, SIGNAL(saveFileData()),
            &currentTrackView_, SLOT(saveData()));

    currentTrackView_.setCurrentTrackMediator(mediator_);
    currentPlaylistView_.setCurrentPlaylistMediator(mediator_);
    fileSystemView_.setFileSystemMediator(mediator_);

    mediator_->setCurrentTrack(currentTrackView_.getModel());
    mediator_->setPlaylist(currentPlaylistView_.getModel());
    mediator_->setFileSystem(fileSystemView_.getModel());
}

void MainView::show() {
    mainWindowWidget_.show();
}

void MainView::close() {
    mainWindowWidget_.close();
}
