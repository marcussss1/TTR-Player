#include "MainWindowView.hpp"

int main(int argc, char** argv) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("/home/marcussss1/2022_2_MidnightSun/project/impl/icons/player.png"));
    MainView w;
    w.show();
    return a.exec();
}
