set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(AppImageLauncherBase STATIC utils.cpp AppImageLauncher.cpp AbstractInstaller.h)
target_link_libraries(AppImageLauncherBase PUBLIC Qt5::Core)
target_include_directories(AppImageLauncherBase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})