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
        projectchrono/5.0.1@jellespijker/testing)
set(CONAN_EXTRA_OPTIONS
        projectchrono:module_irrlicht=False
        qt:shared=False
        qt:with_sqlite3=False
        qt:with_odbc=False
        qt:qtserialbus=False
        qt:qtserialport=False
        qt:qtwayland=False
        qt:commercial=False
        qt:qtandroidextras=False
        qt:qtquicktimeline=False
        qt:qtwebengine=False
        qt:qtconnectivity=False
        qt:qtwebsockets=False
        qt:qtwebchannel=False
        qt:qtwebview=False
        qt:qtnetworkauth=False
        qt:qtwebglplugin=False
        qt:qtsensors=False
        qt:qtremoteobjects=False
        qt:qtnetworkauth=False
        qt:qtvirtualkeyboard=False
        qt:qtgamepad=False
        qt:qtspeech=False
        qt:qt3d=True
        qt:qtquick3d=True
        qt:qtquickcontrols2=True)

include(cmake/Conan.cmake)
set(QT_NO_BEARERMANAGEMENT ON)
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

add_subdirectory(src)
