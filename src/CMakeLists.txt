add_subdirectory(base)
add_subdirectory(appimageservices-interfaces)
add_subdirectory(commands)

set(CMAKE_AUTORCC ON)

add_executable(${CMAKE_PROJECT_NAME} main.cpp ${PROJECT_SOURCE_DIR}/res/icons.qrc)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE AppImageLauncherBase
    PRIVATE AppImageLauncherCommands
    PRIVATE AppImageServicesInterfaces
)

install(
    TARGETS ${CMAKE_PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)