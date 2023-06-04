#pragma once

#include "CurrentTrackUIModel.hpp"
#include "CurrentPlaylistUIModel.hpp"
#include "FileSystemUIModel.hpp"
#include "Mediator.hpp"

class TrackPlaylistModel : public Mediator {
 public:
    virtual void setCurrentTrack(CurrentTrackUIModel* model);
    virtual void setPlaylist(CurrentPlaylistUIModel* model);
    virtual void setFileSystem(FileSystemUIModel* model);

    virtual void notifyTrackPlaylist(Sender* sender, Function function, bool prevNextTrack = false, Track* track = nullptr) override;
    virtual void notifyFileSystemPlaylist(Sender* sender, Function function, std::string path = "") override;
 protected:
    CurrentTrackUIModel* currentTrack_;
    CurrentPlaylistUIModel* playlist_;
    FileSystemUIModel* fileSystem_;
};
