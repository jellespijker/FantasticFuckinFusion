add_executable(FFF main.cpp)

target_compile_definitions(
        FFF
        PRIVATE
        ${CONAN_COMPILE_DEFINITIONS_QT})

target_include_directories(
        FFF
        PRIVATE
        ${CONAN_INCLUDE_DIRS_SPDLOG}
        ${CONAN_INCLUDE_DIRS_DOCOPT.CPP}
        ${CONAN_INCLUDE_DIRS_RANGE-V3})

target_link_libraries(
        FFF
        PRIVATE
        FantasticFuckinFusion
        CONAN_PKG::spdlog
        CONAN_PKG::docopt.cpp
        CONAN_PKG::range-v3
        project_options
        project_warnings)

