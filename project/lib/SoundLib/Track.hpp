#pragma once

#include "ITrack.hpp"
#include <string>
#include <vector>

class Track {
 public:
    explicit Track(ITrack* track);
    ~Track() = default;

    void setData(std::string path,
                 std::string trackName,
                 std::string singer);

    void play() noexcept;
    void pause() noexcept;
    void stop() noexcept;
    void repeat() noexcept;
    void mute() noexcept;

    void setDuration(int position) noexcept;
    void setVolume(int position) noexcept;

    bool isPlaying() const noexcept;
    bool isRepeating() const noexcept;
    bool isMuting() const noexcept;

    std::string getData() {
        return singer_ + " - " + trackName_;
    }

    ITrack* track_;

    std::string path_ = "";
    std::string singer_ = "";
    std::string trackName_ = "";

    bool isPlaying_ = false;
    bool isRepeating_ = false;
    bool isMuting_ = false;

    int currentTime_ = 0;
    int duration_ = 0;
    int volume_ = 50;
};
