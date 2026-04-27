cmake_minimum_required(VERSION 3.19)
project(CodeCampusTerminal LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools Sql Svg Network)

set(CMAKE_AUTOUIC on)
set(CMAKE_AUTOMOC on)
set(CMAKE_AUTORCC on)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_standard_project_setup()

qt_add_executable(CodeCampusTerminal
    WIN32 MACOSX_BUNDLE
    main.cpp
    class/mainwindow.cpp
    class/mainwindow.h
    class/databasemanager.h class/databasemanager.cpp
    class/databaseworker.h class/databaseworker.cpp
    class/addproblem.h class/addproblem.cpp
    class/previewkit.h class/previewkit.cpp
    class/sampleskit.h class/sampleskit.cpp
)

qt_add_translations(
    TARGETS CodeCampusTerminal
    TS_FILES CodeCampusTerminal_en_AS.ts
)

target_link_libraries(CodeCampusTerminal
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Sql
        Qt6::Svg
        Qt6::Network
)

install(TARGETS CodeCampusTerminal
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET CodeCampusTerminal
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
