#include "LeftWallView.hpp"

const int LEFT_BOARD_WIDTH = 200;
const int LEFT_BOARD_HEIGHT = 600;

//////////////////////////////////////// Left Board Widget ////////////////////////////////////////

LeftBoardWidget::LeftBoardWidget(QWidget* parent)
    : leftBoard_(new QWidget(parent)) {
    leftBoard_->setObjectName("leftBoard");
    leftBoard_->setGeometry(QRect(0, 0,
                                  LEFT_BOARD_WIDTH,
                                  LEFT_BOARD_HEIGHT - 125));
}

LeftBoardWidget::~LeftBoardWidget() {
    delete leftBoard_;
}

//////////////////////////////////////// Left Board View ////////////////////////////////////////

LeftBoardView::LeftBoardView(QWidget* parent)
    : leftBoardWidget_(parent) {}
