#pragma once

#include "Mediator.hpp"

class FileSystemUIModel : public Sender {
 public:
    void setFileSystemMediator(Mediator* mediator);
    void openFile(std::string path);    
};
