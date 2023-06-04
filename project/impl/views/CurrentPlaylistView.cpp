#include "CurrentPlaylistView.hpp"

CurrentPlaylistView::CurrentPlaylistView(CurrentPlaylistUIModel* model, QWidget* parent)
    : currentTracksCount_(0),
      model_(model),
      controller_(new CurrentPlaylistController(model)),
      currentPlaylistWidget_(new QTableWidget(parent)),
      menu_(new QMenu(parent)),
      addTrack_(new QAction(currentPlaylistWidget_)),
      deleteTrack_(new QAction(currentPlaylistWidget_)),
      chooseTrack_(new QAction(currentPlaylistWidget_)) {

    currentPlaylistWidget_->setGeometry(QRect(0, 25, 675, 450));

    connect(currentPlaylistWidget_, &QTableWidget::clicked,
            this, &CurrentPlaylistView::trackClicked);

    connect(addTrack_, SIGNAL(triggered()),
            this, SLOT(addTrackInWidget())); // .. моя вьюшка триггерит ... а не main view

    connect(deleteTrack_, SIGNAL(triggered()),
            this, SLOT(removeCurrentTrack()));

    connect(chooseTrack_, SIGNAL(triggered()),
            this, SLOT(chooseTrackInWidget()));

    addTrack_->setText("Добавить трек");
    chooseTrack_->setText("Выбрать трек");
    deleteTrack_->setText("Удалить текущий трек");

    menu_->addAction(addTrack_);
    menu_->addAction(chooseTrack_);
    menu_->addAction(deleteTrack_);
}

void CurrentPlaylistView::addTrackInWidget(QString path, bool flag) { // триггерится другой вьюшкой
    auto size = currentPlaylistWidget_->rowCount();

    currentPlaylistWidget_->setRowCount(size + 1);
    currentPlaylistWidget_->setColumnCount(1);

    currentPlaylistWidget_->verticalHeader()->setVisible(false);
    currentPlaylistWidget_->horizontalHeader()->setVisible(false);

    currentPlaylistWidget_->setItem(size, size, new QTableWidgetItem);
    currentPlaylistWidget_->setColumnWidth(size, 675); 
    currentPlaylistWidget_->setRowHeight(size, 50);   

    currentPlaylistWidget_->setItem(size, 0, new QTableWidgetItem(path));
    currentPlaylistWidget_->item(size, 0)->setTextColor(Qt::white);

    if (flag) {
        currentPlaylistWidget_->setGeometry(QRect(0, 25, 675, 450 - currentTracksCount_ * 40));
        ++currentTracksCount_;
    }
}

void CurrentPlaylistView::removeCurrentTrack() {
    if (currentTracksCount_ == 0) {
        return;
    }
    QItemSelectionModel* selectModel = currentPlaylistWidget_->selectionModel();
    if (selectModel->hasSelection()) {
        if (currentTracksCount_ != 1) {
            currentPlaylistWidget_->setGeometry(QRect(0, 25, 675, 450 - (currentTracksCount_ - 2) * 40));
        } else {
            currentPlaylistWidget_->setGeometry(QRect(0, 25, 675, 450));
        }

        --currentTracksCount_;
       
        emit deleteCurrentTrack(currentPlaylistWidget_->item(selectModel->selectedRows().first().row(), 0)->text(), selectModel->selectedRows().first().row());
    }
}

void CurrentPlaylistView::chooseTrackInWidget() {
    QItemSelectionModel* selectModel = currentPlaylistWidget_->selectionModel();
    if (selectModel->hasSelection()) {
        if (currentTracksCount_ != 0) {
            currentPlaylistWidget_->setGeometry(QRect(0, 25, 675, 450 - currentTracksCount_ * 40));
        }
        emit currentTrackChanged(currentPlaylistWidget_->item(selectModel->selectedRows().first().row(), 0)->text(), selectModel->selectedRows().first().row(), true);
        ++currentTracksCount_;
    }
}

void CurrentPlaylistView::trackClicked() {
    menu_->popup(currentPlaylistWidget_->viewport()->mapToGlobal(QPoint(250, 250)));
}

void CurrentPlaylistView::setCurrentPlaylistMediator(Mediator* mediator) {
    model_->setCurrentPlaylistMediator(mediator);
}

CurrentPlaylistUIModel* CurrentPlaylistView::getModel() {
    return model_;
}
