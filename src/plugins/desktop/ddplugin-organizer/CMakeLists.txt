cmake_minimum_required(VERSION 3.10)

project(ddplugin-organizer)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(EXT_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/../desktoputils/widgetutil.h
    )

FILE(GLOB_RECURSE CORE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.json"
)

# Qt6
if (DFM_BUILD_WITH_QT6)
    include(ddplugin-organizer-qt6.cmake)
else()
    include(ddplugin-organizer-qt5.cmake)
endif()


# install dconfig files.
INSTALL_DCONFIG("org.deepin.dde.file-manager.desktop.organizer.json")
