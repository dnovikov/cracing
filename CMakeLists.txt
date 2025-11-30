cmake_minimum_required(VERSION 3.10)

project(Racing VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build

set(RACING_EXEC_NAME cracing)

add_executable(${RACING_EXEC_NAME}
    src/game.cpp
    src/info.cpp
    src/vehicle.cpp
    src/track.cpp
    src/racing.cpp
)

target_include_directories(${RACING_EXEC_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

target_include_directories(${RACING_EXEC_NAME} PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(${RACING_EXEC_NAME} PRIVATE ${CURSES_LIBRARIES})

# Tests

Include(FetchContent)
FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.11.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests
    tests/vehicle.cpp
    src/vehicle.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)
