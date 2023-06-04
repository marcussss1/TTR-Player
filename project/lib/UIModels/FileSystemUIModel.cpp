#include "FileSystemUIModel.hpp"

void FileSystemUIModel::setFileSystemMediator(Mediator* mediator) {
    mediator_ = mediator;
}

void FileSystemUIModel::openFile(std::string path) {
    mediator_->notifyFileSystemPlaylist(this, OpenFile, path);
}
