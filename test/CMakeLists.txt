find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Test)

add_subdirectory(test-base)
add_subdirectory(commands)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(AppImageLauncherTests AppImageLauncherTests.cpp)
target_link_libraries(AppImageLauncherTests AppImageLauncherBase AppImageLauncherTestBase Qt5::Test)

add_test(NAME AppImageLauncherTests COMMAND AppImageLauncherTests)

add_test(NAME AppImageLauncherTests_KeepQtArgs
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/AppImageLauncherTests_KeepQtArgs.sh ${PROJECT_BINARY_DIR}/src/AppImageLauncher)


# Allways must be at the end
enable_testing()