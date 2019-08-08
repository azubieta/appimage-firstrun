cmake_policy(SET CMP0079 NEW)

add_subdirectory(base)
add_subdirectory(appimageservices-interfaces)
add_subdirectory(commands)

add_executable(AppImageLauncher main.cpp)
target_link_libraries(
    AppImageLauncher
    PRIVATE AppImageLauncherBase
    PRIVATE AppImageLauncherCommands
    PRIVATE AppImageServicesInterfaces
    PRIVATE Qt5::Core
    PRIVATE Qt5::Widgets
)