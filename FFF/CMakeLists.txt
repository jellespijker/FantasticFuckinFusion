add_executable(FFF main.cpp)

target_compile_definitions(FFF
        PRIVATE
            ${CONAN_COMPILE_DEFINITIONS_QT})

target_compile_options(FFF
        PRIVATE
            -fPIC)

target_link_libraries(FFF
        PRIVATE
            project_options
            project_warnings)

target_link_libraries(FFF
        PRIVATE
            FantasticFuckinFusion
            CONAN_PKG::spdlog
            CONAN_PKG::docopt.cpp
            CONAN_PKG::range-v3
            CONAN_PKG::qt
            Qt::Core
            Qt::Gui
            Qt::Widgets
            Qt::3DCore
            Qt::3DExtras
            Qt::3DRender
            Qt::3DInput
        )

