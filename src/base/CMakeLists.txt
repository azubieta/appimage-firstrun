add_library(AppImageLauncherBase STATIC AppImageLauncher.cpp utils.cpp AbstractInspector.cpp AbstractInspector.h)
target_link_libraries(AppImageLauncherBase PUBLIC Qt5::Core)
target_include_directories(AppImageLauncherBase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})