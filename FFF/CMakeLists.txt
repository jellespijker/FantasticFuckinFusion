add_executable(FFF main.cpp)

target_compile_options(
        FFF
        PRIVATE
        -fPIC)

target_compile_definitions(
        FFF
        PRIVATE
        ${CONAN_COMPILE_DEFINITIONS_QT})

target_include_directories(
        FFF
        PRIVATE
        ${CONAN_INCLUDE_DIRS_SPDLOG}
        ${CONAN_INCLUDE_DIRS_DOCOPT.CPP}
        ${CONAN_INCLUDE_DIRS_RANGE-V3}
        ${CONAN_INCLUDE_DIRS_QT})

target_link_libraries(
        FFF
        PRIVATE
        CONAN_PKG::qt
        CONAN_PKG::spdlog
        CONAN_PKG::docopt.cpp
        CONAN_PKG::range-v3
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::3DCore
        Qt5::3DExtras
        Qt5::3DRender
        Qt5::3DInput
        project_options
        project_warnings)

