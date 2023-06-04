#pragma once

#include "FileSystemUIModel.hpp"

class FileSystemController {
 public:
    explicit FileSystemController(FileSystemUIModel* model);
    void openFile(std::string path);
 private:
    FileSystemUIModel* model_;
};
