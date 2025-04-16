cmake_minimum_required(VERSION 3.10)
project(DigitalFilter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find PortAudio package
find_package(PkgConfig REQUIRED)
pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)

add_executable(digital_filter
    main.cpp
    DigitalFilter.cpp
)

target_include_directories(digital_filter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(digital_filter PRIVATE ${PORTAUDIO_INCLUDE_DIRS})
target_link_libraries(digital_filter PRIVATE ${PORTAUDIO_LIBRARIES}) 