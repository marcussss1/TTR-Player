CMAKE_MINIMUM_REQUIRED(VERSION 2.9)

PROJECT(tests)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Werror -Wextra -Wpedantic -Wall -L /lib64 -lrt -lm -lpthread")

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Multimedia REQUIRED)

INCLUDE_DIRECTORIES("${PROJECT_SOURCES_DIR} impl/icons")
INCLUDE_DIRECTORIES("${PROJECT_SOURCES_DIR} impl/style")
INCLUDE_DIRECTORIES("${PROJECT_SOURCES_DIR} impl/views")

INCLUDE_DIRECTORIES("${PROJECT_SOURCES_DIR} lib/Controllers")
INCLUDE_DIRECTORIES("${PROJECT_SOURCES_DIR} lib/FileLib")
INCLUDE_DIRECTORIES("${PROJECT_SOURCES_DIR} lib/Mediator")
INCLUDE_DIRECTORIES("${PROJECT_SOURCES_DIR} lib/SoundLib")
INCLUDE_DIRECTORIES("${PROJECT_SOURCES_DIR} lib/SoundLibWithOuterDependncies")
INCLUDE_DIRECTORIES("${PROJECT_SOURCES_DIR} lib/UIModels")

INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDES})
INCLUDE_DIRECTORIES(${Qt5Multimedia_INCLUDES})

SET(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")


SET(LIB 
        lib/Controllers/CurrentPlaylistController.cpp
        lib/Controllers/CurrentTrackController.cpp
        lib/Controllers/FileSystemController.cpp
        lib/Mediator/GlobalModel.cpp
        lib/SoundLib/Parser.cpp
        lib/SoundLib/Playlist.cpp
        lib/SoundLib/Track.cpp
        lib/SoundLibWithOuterDependncies/QTrack.cpp
        lib/UIModels/CurrentPlaylistUIModel.cpp
        lib/UIModels/CurrentTrackUIModel.cpp
        lib/UIModels/FileSystemUIModel.cpp)

SET(IMPL
        impl/views/CurrentPlaylistView.cpp
        impl/views/CurrentTrackView.cpp
        impl/views/FileSystemView.cpp
        impl/views/LeftWallView.cpp
        impl/views/MainWindowView.cpp
        impl/views/TitleBarButtonsView.cpp)

ADD_EXECUTABLE(mplayer main.cpp ${LIB} ${IMPL})
TARGET_LINK_LIBRARIES(mplayer ${Qt5Widgets_LIBRARIES} ${Qt5Multimedia_LIBRARIES} pthread stdc++fs)
