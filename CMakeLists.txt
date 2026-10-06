cmake_minimum_required(VERSION 3.25)
project(CppForCVRobotics LANGUAGES CXX)

# --- Language settings -------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Put every .exe in one folder: build/<preset>/bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- Shared helpers (common/check.hpp) ---------------------------------------
add_library(course_common INTERFACE)
target_include_directories(course_common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/common)

# course_warnings(<target> [STUB])
# Turns on the course's compiler flags. STUB = code with unfinished TODO stubs:
# those ignore their parameters, so that one noisy warning is hidden.
function(course_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive- /utf-8 /EHsc)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    if("STUB" IN_LIST ARGN)
        if(MSVC)
            target_compile_options(${target} PRIVATE /wd4100)
        else()
            target_compile_options(${target} PRIVATE -Wno-unused-parameter)
        endif()
    endif()
endfunction()

# add_exercise(<target-name> <source files...>)
# Creates one executable with the course's flags and helpers.
# Targets named dayNN_exNN are treated as STUB code.
function(add_exercise name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name} PRIVATE course_common)
    if(name MATCHES "_ex[0-9]+$")
        course_warnings(${name} STUB)
    else()
        course_warnings(${name})
    endif()
endfunction()

# --- Days --------------------------------------------------------------------
# Each dayNN/ folder that has a CMakeLists.txt is added automatically.
foreach(n RANGE 1 20)
    if(n LESS 10)
        set(day "day0${n}")
    else()
        set(day "day${n}")
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${day}/CMakeLists.txt)
        add_subdirectory(${day})
    endif()
endforeach()
