cmake_minimum_required(VERSION 3.31)
project(sadplay VERSION 1.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBBINIO REQUIRED libbinio)
pkg_check_modules(ADPLUG REQUIRED adplug)
pkg_check_modules(FFTW3 REQUIRED fftw3)
pkg_check_modules(SDL2 REQUIRED SDL2)

include_directories(
    ${LIBBINIO_INCLUDE_DIRS}
    ${ADPLUG_INCLUDE_DIRS}
    ${FFTW3_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
)

link_directories(
    ${LIBBINIO_LIBRARY_DIRS}
    ${ADPLUG_LIBRARY_DIRS}
    ${FFTW3_LIBRARY_DIRS}
    ${SDL2_LIBRARY_DIRS}
)

include(CheckCXXSourceCompiles)

set(SADPLAY_SOURCES
    src/adplug_player.cc
    src/display.cc
    src/frequency_bar.cc
    src/main_support.cc
    src/main.cc
    src/sadplay_args.cc
    src/sadplay.cc
    src/sdl_channel_bar.cc
    src/sdl_driver.cc
    src/spectrum_analyzer.cc
    src/texts.cc
)
add_executable(sadplay ${SADPLAY_SOURCES})
set_property(TARGET sadplay PROPERTY CXX_STANDARD 11)
target_include_directories(sadplay PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(sadplay PRIVATE 
    ${LIBBINIO_LIBRARIES}
    ${ADPLUG_LIBRARIES}
    ${FFTW3_LIBRARIES}
    ${SDL2_LIBRARIES}
)

set(CMAKE_REQUIRED_INCLUDES
    ${LIBBINIO_INCLUDE_DIRS}
    ${ADPLUG_INCLUDE_DIRS}
)

set(CMAKE_REQUIRED_LINK_DIRECTORIES
    ${LIBBINIO_LIBRARY_DIRS}
    ${ADPLUG_LIBRARY_DIRS}
)

set(CMAKE_REQUIRED_LIBRARIES ${LIBBINIO_LIBRARIES} ${ADPLUG_LIBRARIES})

check_cxx_source_compiles(" 
    #include <adplug/surroundopl.h>
    #include <adplug/temuopl.h>
    void createOPLProps(COPLprops* coplprops) {
      coplprops->opl = new CTemuopl(44100, true, false);
      coplprops->use16bit = true;
      coplprops->stereo = false;
    }

    int main() {
        COPLprops opl[2];
        createOPLProps(opl);
        createOPLProps(opl + 1); 
        CSurroundopl csurroundopl(opl, opl + 1, true);
        return 0;
    }
" HAVE_ADPLUG_COPLPROPS)
if (HAVE_ADPLUG_COPLPROPS)
    target_compile_definitions(sadplay PRIVATE HAVE_ADPLUG_COPLPROPS)
endif()

target_compile_definitions(sadplay PUBLIC PACKAGE_VERSION="${PROJECT_VERSION}")

install(TARGETS sadplay)