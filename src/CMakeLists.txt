add_executable(fff main.cpp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#target_include_directories(fff
#        PUBLIC
#        $<INSTALL_INTERFACE:include>
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#        PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}/src)
#
target_compile_options(fff PRIVATE -fPIC)

target_include_directories(
        fff
        PRIVATE
#            ${CONAN_INCLUDE_DIRS_PROJECTCHRONO}
            ${CONAN_INCLUDE_DIRS_QT})

target_link_libraries(
        fff
        PUBLIC
            CONAN_PKG::projectchrono
            CONAN_PKG::qt
        PRIVATE
            project_options
            project_warnings)
