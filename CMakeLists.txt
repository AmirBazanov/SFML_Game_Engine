cmake_minimum_required(VERSION 3.13)
project(SFML_Game_Engine)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(${PROJECT_NAME} WIN64 ${SOURCE_FILES})
else ()
    add_executable(${PROJECT_NAME} main.cpp)
endif ()


set(SFML_ROOT "libs/SFML-2.5.1")
set(SFML_DIR "libs/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 REQUIRED COMPONENTS audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    link_directories(${SFML_LINK_DIR})
    target_link_libraries(${PROJECT_NAME} sfml-system sfml-graphics sfml-audio)
else ()
    message("SFML NOT FOUND")
endif()
