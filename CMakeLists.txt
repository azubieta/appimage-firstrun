cmake_minimum_required(VERSION 3.10)
project(
    AppImageLauncher
    VERSION 3.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
include(FeatureSummary)
include(GNUInstallDirs)

set(QT_MIN_VERSION "5.8.0")
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets DBus)

add_subdirectory(src)
add_subdirectory(test)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
