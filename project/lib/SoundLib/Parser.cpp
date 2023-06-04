#include "Parser.hpp"

Track* Parser::parsingPath(std::string path) {
    if (!isFileExist(path)) {
        return nullptr;
    }
    if (!isAudioFile(path)) {
        return nullptr;
    }

    auto qtrack = new QTrack;
    qtrack->setCurrentTrack(QString::fromStdString(path));
    auto track = new Track(qtrack);
    track->setData(path,
                   path.substr(0, path.find('-')),
                   path.substr(path.find('-') + 1));
    return track;
}

bool Parser::isFileExist(std::string path) {
    if (std::experimental::filesystem::exists(path)) {
        return true;
    }
    return false;
}

bool Parser::isAudioFile(std::string path) {
    std::reverse(path.begin(), path.end());
    auto expansion = path.substr(0, path.find('.'));
    std::reverse(expansion.begin(), expansion.end());
    if (expansion == "mp3") {
        return true;
    }
    if (expansion == "wav") {
        return true;
    }
    if (expansion == "ogg") {
        return true;
    }
    if (expansion == "mid") {
        return true;
    }
    if (expansion == "kar") {
        return true;
    }
    return false;
}
