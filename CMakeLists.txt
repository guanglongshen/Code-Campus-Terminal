cmake_minimum_required(VERSION 3.19)
project(CodeCampusTerminal LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(CodeCampusTerminal
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

qt_add_translations(
    TARGETS CodeCampusTerminal
    TS_FILES CodeCampusTerminal_en_AS.ts
)

target_link_libraries(CodeCampusTerminal
    PRIVATE
        Qt::Core
        Qt::Widgets
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
