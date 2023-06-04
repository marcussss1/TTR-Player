#include "FileSystemView.hpp"

const int MENU_BAR_WIDTH = 200;
const int MENU_BAR_HEIGHT = 25;

FileSystemView::FileSystemView(QWidget* parent) 
    : menuBarWidget_(new QMenuBar(parent)),
      model_(new FileSystemUIModel),
      controller_(new FileSystemController(model_)) {

    menuBarWidget_->setGeometry(QRect(0, 0, 200, 25));
    menuAddFile_ = menuBarWidget_->addMenu("Файл");
    actionAddFile_ = menuAddFile_->addAction("Открыть файл");
    actionSaveFile_ = menuAddFile_->addAction("Сохранить файл");
    connect(actionAddFile_, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(actionSaveFile_, SIGNAL(triggered()), this, SLOT(saveFile()));
}

void FileSystemView::openFile() {
    auto path  = QFileDialog::getOpenFileNames(menuBarWidget_,
                                               "Select Files", 
                                               "/home/marcussss1/2022_2_MidnightSun/ManuallyCase/",
                                               "WAV TXT Files (*.wav *.txt)");
    if (!path.empty()) {
        if (path.join("")[path.join("").size() - 1] == 't') {
            openTextFile(path.join(""));
            return;
        }
        controller_->openFile(path.join("").toStdString());
        emit openFile(path.join(""), false);
    }
}

void FileSystemView::saveFile() {
    emit saveFileData();
}

void FileSystemView::openTextFile(QString path) {
    std::ifstream file(path.toStdString());
    if (file.is_open()) {
        std::string line;
        std::vector<std::string> arr;
        while (std::getline(file, line)) {
            if (arr.size() == 5) {
                emit addTrack(QString::fromStdString(arr[0]),
                              atoi(arr[1].c_str()),
                              atoi(arr[2].c_str()),
                              atoi(arr[3].c_str()),
                              atoi(arr[4].c_str()));
                controller_->openFile(arr[0]);
                emit openFile(QString::fromStdString(arr[0]), true);
                arr.clear();
            }
            arr.push_back(line);
        }
        file.close();
    }
}

void FileSystemView::setFileSystemMediator(Mediator* mediator) {
    model_->setFileSystemMediator(mediator);
}

FileSystemUIModel* FileSystemView::getModel() {
    return model_;
}

FileSystemView::~FileSystemView() {
    delete menuBarWidget_;
}
