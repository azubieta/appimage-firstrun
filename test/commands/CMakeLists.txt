# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

## Launch Command
add_executable(LaunchCommandTests LaunchCommandTest.cpp LaunchCommandFakeAssistant.cpp)
target_link_libraries(LaunchCommandTests AppImageLauncherCommands AppImageLauncherTestBase Qt5::Test)
add_test(NAME LaunchCommandTests COMMAND LaunchCommandTests)

## Launch Command Assistant
add_executable(LaunchCommandAssistantTests LaunchCommandAssistantTests.cpp)
target_link_libraries(LaunchCommandAssistantTests AppImageLauncherCommands AppImageLauncherTestBase Qt5::Test)
add_test(NAME LaunchCommandAssistantTests COMMAND LaunchCommandAssistantTests)