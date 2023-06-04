#include "TitleBarButtonsView.hpp"

//////////////////////////////////////// Coordinats x ////////////////////////////////////////

const int CLOSE_X = 765 - 125;
const int ZOOM_X = 730 - 125;
const int MINIMIZE_X = 690 - 125;

//////////////////////////////////////// Coordinats y ////////////////////////////////////////

const int CLOSE_Y = 0;
const int ZOOM_Y = 0;
const int MINIMIZE_Y = 0;

//////////////////////////////////////// Widths ////////////////////////////////////////

const int OPTIONS_WINDOW_WIDTH = 800;
const int BUTTON_WIDTH = 30;

//////////////////////////////////////// Heights ////////////////////////////////////////

const int OPTIONS_WINDOW_HEIGHT = 25;
const int BUTTON_HEIGHT = 25;

//////////////////////////////////////// Names ////////////////////////////////////////

const char* CLOSE_NAME = "close";
const char* ZOOM_NAME = "zoom";
const char* MINIMIZE_NAME = "minimize";

ITitleBarButton::ITitleBarButton(QWidget* parent)
    : button_(new QPushButton(parent)) {}

ITitleBarButton::~ITitleBarButton() {
    delete button_;
}

void ITitleBarButton::setStyle(int buttonX, int buttonY,
                               int buttonWidth, int buttonHeight,
                               const char* buttonName) {
    button_->setObjectName(buttonName);
    button_->setGeometry(QRect(buttonX, buttonY,
                               buttonWidth, buttonHeight));
}

CloseButton::CloseButton(QWidget* parent)
    : ITitleBarButton(parent) {
    setStyle(CLOSE_X, CLOSE_Y,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             CLOSE_NAME);
}

ZoomButton::ZoomButton(QWidget* parent)
    : ITitleBarButton(parent) {
    setStyle(ZOOM_X, ZOOM_Y,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             ZOOM_NAME);
}

MinimizeButton::MinimizeButton(QWidget* parent)
    : ITitleBarButton(parent) {
    setStyle(MINIMIZE_X, MINIMIZE_Y,
             BUTTON_WIDTH, BUTTON_HEIGHT,
             MINIMIZE_NAME);
}

TitleBarButtonsWidget::TitleBarButtonsWidget(QWidget* parent)
    : titleBarButtonsWidget_(new QWidget(parent)),
      close_(parent),
      zoom_(parent),
      minimize_(parent) {

    connect(close_.button_, SIGNAL(clicked()), this, SLOT(close()));

    titleBarButtonsWidget_->setObjectName("optionsWindow");
    titleBarButtonsWidget_->setGeometry(QRect(0, 0, OPTIONS_WINDOW_WIDTH, OPTIONS_WINDOW_HEIGHT));
}

TitleBarButtonsWidget::~TitleBarButtonsWidget() {
    delete titleBarButtonsWidget_;
}

TitleBarButtonsView::TitleBarButtonsView(QWidget* parent)
    : titleBarButtonsWidget_(parent) {}
