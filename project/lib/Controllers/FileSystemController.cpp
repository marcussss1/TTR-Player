#include "FileSystemController.hpp"

FileSystemController::FileSystemController(FileSystemUIModel* model)
    : model_(model) {}

void FileSystemController::openFile(std::string path) {
    model_->openFile(path);
}
