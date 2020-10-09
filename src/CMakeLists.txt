add_executable(fff main.cpp)

target_compile_options(fff PRIVATE -fPIC)

target_include_directories(
        fff
        PRIVATE
            ${CONAN_INCLUDE_DIRS_QT})

target_link_libraries(
        fff
        PUBLIC
            CONAN_PKG::projectchrono
            CONAN_PKG::qt
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

qt_import_plugins(fff
                  INCLUDE
                    Qt::QTiffPlugin
                    Qt::QGifPlugin
                    Qt::QJpegPlugin)
