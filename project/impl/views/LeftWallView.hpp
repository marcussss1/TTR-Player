#pragma once

#include <QWidget>

//////////////////////////////////////// Left Board Widget ////////////////////////////////////////

class LeftBoardWidget {
  public:
    explicit LeftBoardWidget(QWidget* parent);
    ~LeftBoardWidget();

    LeftBoardWidget(const LeftBoardWidget& rhs) = delete;
    LeftBoardWidget(LeftBoardWidget&& rhs) = delete;

    LeftBoardWidget& operator=(const LeftBoardWidget& rhs) = delete;
    LeftBoardWidget& operator=(LeftBoardWidget&& rhs) = delete;

  private:
    QWidget* leftBoard_;
};

//////////////////////////////////////// Left Board View ////////////////////////////////////////

class LeftBoardView {
 public:
    explicit LeftBoardView(QWidget* parent);
    ~LeftBoardView() = default;
 private:
    LeftBoardWidget leftBoardWidget_;
};
