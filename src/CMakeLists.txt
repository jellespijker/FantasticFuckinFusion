add_executable(FantasticFuckinFusion main.cpp)

target_compile_options(
        FantasticFuckinFusion
        PRIVATE
            -fPIC)

target_compile_definitions(
        FantasticFuckinFusion
        PRIVATE
            ${CONAN_COMPILE_DEFINITIONS_PROJECTCHRONO}
            ${CONAN_COMPILE_DEFINITIONS_QT})

target_include_directories(
        FantasticFuckinFusion
        PRIVATE
            ${CONAN_INCLUDE_DIRS_SPDLOG}
            ${CONAN_INCLUDE_DIRS_PROJECTCHRONO}
            ${CONAN_INCLUDE_DIRS_QT})

target_link_libraries(
        FantasticFuckinFusion
        PUBLIC
            CONAN_PKG::projectchrono
            CONAN_PKG::qt
            CONAN_PKG::spdlog
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            Qt5::3DCore
            Qt5::3DExtras
            Qt5::3DRender
            Qt5::3DInput
        PRIVATE
            project_options
            project_warnings)

qt_import_plugins(FantasticFuckinFusion
                  INCLUDE
                    Qt::QTiffPlugin
                    Qt::QGifPlugin
                    Qt::QJpegPlugin)
