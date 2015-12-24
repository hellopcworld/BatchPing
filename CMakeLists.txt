cmake_minimum_required(VERSION 2.8.4)
project(splitStr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set (CMAKE_CXX_COMPILER "clang")
include_directories(/usr/local/include/boost/)
include_directories(/usr/local/include/)
include_directories(/usr/local/include/hiredis/)
include_directories(/usr/local/inutil)

set(SOURCE_FILES
    AdListSortThread.h
    consistent_hash_map.hpp
    masspinger/Pinger.cpp
    masspinger/Host.cpp
    main.cpp)

link_directories(/usr/local/lib/)
link_libraries(splitStr /usr/local/lib/libcityhash.a)

find_library(LIB_boost_thread NAMES boost_thread)
find_library(LIB_boost_system NAMES boost_system)
find_library(LIB_boost_date NAMES boost_date_time)
find_library(LIB_pthread NAMES pthread)
find_library(LIB_hiredis NAMES hiredis)

add_executable(splitStr ${SOURCE_FILES} masspinger/PingManager.h)

target_link_libraries(splitStr
    #${LIB_cityhash}
    ${LIB_pthread}
    #/usr/lib/x86_64-linux-gnu/libpthread.so
    /usr/local/inutil/libinvutil.a
    ${LIB_hiredis}
    ${LIB_boost_system}
    ${LIB_boost_date}
    ${LIB_boost_thread}
    -lm
    -lstdc++
    )
