#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

class ITitleBarButton : public QMainWindow {
 Q_OBJECT
 public:
    friend class CurrentTrackView;
    explicit ITitleBarButton(QWidget* parent = nullptr);
    ~ITitleBarButton();

    void setStyle(int buttonX, int buttonY,
                  int buttonWidth, int buttonHeight,
                  const char* buttonName);
    QPushButton* button_;
};

struct CloseButton : public ITitleBarButton {
 public:
    explicit CloseButton(QWidget* parent);
};

struct ZoomButton : public ITitleBarButton {
 public:
    explicit ZoomButton(QWidget* parent);
};

struct MinimizeButton : public ITitleBarButton {
 public:
    explicit MinimizeButton(QWidget* parent);
};

class TitleBarButtonsWidget : public QObject {
 Q_OBJECT
 public:
    explicit TitleBarButtonsWidget(QWidget* parent);
    ~TitleBarButtonsWidget();

    TitleBarButtonsWidget(const TitleBarButtonsWidget& rhs) = delete;
    TitleBarButtonsWidget(TitleBarButtonsWidget&& rhs) = delete;

    TitleBarButtonsWidget& operator=(const TitleBarButtonsWidget& rhs) = delete;
    TitleBarButtonsWidget& operator=(TitleBarButtonsWidget&& rhs) = delete;

 private slots:
    void close() {
      QWidget* a = nullptr;
      a->saveGeometry();
    }

 private:
    QWidget* titleBarButtonsWidget_;

    CloseButton close_;
    ZoomButton zoom_;
    MinimizeButton minimize_;
};

class TitleBarButtonsView {
 public:
    explicit TitleBarButtonsView(QWidget* parent);
    ~TitleBarButtonsView() = default;
    TitleBarButtonsWidget titleBarButtonsWidget_;
};
