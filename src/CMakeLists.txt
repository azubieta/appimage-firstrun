add_subdirectory(base)
add_subdirectory(appimageservices-interfaces)
add_subdirectory(commands)

add_executable(AppImageLauncher main.cpp)
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