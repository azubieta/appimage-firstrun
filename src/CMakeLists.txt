add_subdirectory(base)
add_subdirectory(appimageservices-interfaces)
add_subdirectory(commands)

set(CMAKE_AUTORCC ON)

add_executable(AppImageLauncher main.cpp ${PROJECT_SOURCE_DIR}/res/icons.qrc)

target_link_libraries(
    AppImageLauncher
    PRIVATE AppImageLauncherBase
    PRIVATE AppImageLauncherCommands
    PRIVATE AppImageServicesInterfaces
)

install(
    TARGETS AppImageLauncher
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)