cmake_minimum_required(VERSION 3.15)

project(FantasticFuckinFusion CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if(ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(project_options INTERFACE -ftime-trace)
    endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" ON)
if (BUILD_SHARED_LIBS)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif (BUILD_SHARED_LIBS)

option(ENABLE_TESTING "Enable Test Builds" ON)
option(ENABLE_FUZZING "Enable Fuzzing Builds" OFF)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
    #
    # consider breaking this out per project as necessary
    target_precompile_headers(
            project_options
            INTERFACE
            <vector>
            <string>
            <map>
            <utility>)
endif()

# Set up some extra Conan dependencies based on our needs before loading Conan
set(CONAN_EXTRA_REQUIRES
        zlib/1.2.11@conan/stable
        freetype/2.10.1
        fontconfig/2.13.91@jellespijker/testing
        qt/5.15.1@bincrafters/stable
        projectchrono/5.0.1@jellespijker/testing
        range-v3/0.11.0)
set(CONAN_EXTRA_OPTIONS
        projectchrono:module_irrlicht=False
        qt:shared=False
        qt:qtsvg=True
        qt:qt3d=True
        qt:qtimageformats=True
        qt:qtquick3d=True
        qt:with_icu=False  # FIXME: gives error when compiling with C++20
        qt:with_mysql=False  # FIXME: gives error when compiling with C++20
        )

include(cmake/Conan.cmake)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets 3DCore 3DExtras 3DRender 3DInput)
set(QT_NO_BEARERMANAGEMENT ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

run_conan()


if(ENABLE_TESTING)
    enable_testing()
    message("Building Tests. Be sure to check out test/constexpr_tests for constexpr testing")
    add_subdirectory(test)
endif()

if(ENABLE_FUZZING)
    message("Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
    add_subdirectory(fuzz_test)
endif()

# DEFINE BINARY AND LIBS PATHS ACCORDING TO GNU STANDARDS
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set(SRC_FILES
        src/Interpreter.cpp)

set(HDR_FILES
        include/FFF/Interpreter.h)

add_library(FantasticFuckinFusion SHARED ${SRC_FILES} ${HDR_FILES})
target_link_libraries(FantasticFuckinFusion PRIVATE project_options project_warnings)

target_include_directories(FantasticFuckinFusion PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

option(ENABLE_STANDALONE "Create a standalone instance" ON)
if(ENABLE_STANDALONE)
    message("Building FFF standalone program")
    add_subdirectory(FFF)
endif()

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS FantasticFuckinFusion EXPORT FantasticFuckinFusionConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT FantasticFuckinFusionConfig DESTINATION share/piv_extrusion/cmake)

# This makes the project importable from the build directory
export(TARGETS FantasticFuckinFusion FILE FantasticFuckinFusionConfig.cmake)
