set(
    AppImageLauncherCommandsSources
    GuiCommandsFactory.cpp
    LaunchCommand.cpp
    LaunchCommandAssistantDialog.cpp
    LaunchCommandAssistantDialog.ui
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC  ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(AppImageLauncherCommands STATIC ${AppImageLauncherCommandsSources})
target_link_libraries(AppImageLauncherCommands PUBLIC AppImageLauncherBase Qt5::Core Qt5::Widgets)
target_include_directories(AppImageLauncherCommands PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
