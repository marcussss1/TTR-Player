#pragma once

#include "Track.hpp"

enum Function {
// Значения, указывающие какие функции нужно стриггерить у UI моделей
    OpenFile,
    Shuffle,
    PreviousTrack,
    NextTrack,
    Repeat,
    DurationEnd,
    NewCurrentTrack,
    DeletedTrackIsCurrent
};

enum Status {
    Success,
    Failure
};

class Sender;

struct Mediator {
    Mediator() = default;
    virtual void notifyTrackPlaylist(Sender* sender, Function function, bool prevNextTrack = false, Track* track = nullptr) = 0;
    virtual void notifyFileSystemPlaylist(Sender* sender, Function function, std::string path = "") = 0;
};

class Sender {
 public:
    Sender() = default;
    explicit Sender(Mediator *mediator);
 protected:
    Mediator* mediator_;
};
