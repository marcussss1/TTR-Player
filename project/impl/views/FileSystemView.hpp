#pragma once

#include "FileSystemController.hpp"

#include <fstream>
#include <iostream>

#include <QAction>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenuBar>
#include <QWidget>


class FileSystemView : public QMainWindow {
 Q_OBJECT
 public:
    explicit FileSystemView(QWidget* parent);
    ~FileSystemView();

    void setFileSystemMediator(Mediator* mediator);
    FileSystemUIModel* getModel();

 signals:
    void openFile(QString, bool);
    void addTrack(QString, int, int, int, int);
    void saveFileData();

 private slots:
    void openFile();
    void saveFile();

 private:
    void openTextFile(QString path);


    QMenuBar* menuBarWidget_;
    QMenu* menuAddFile_;
    QAction* actionAddFile_;
    QAction* actionSaveFile_;

    FileSystemUIModel* model_;
    FileSystemController* controller_;
};
