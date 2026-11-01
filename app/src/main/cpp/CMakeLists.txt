cmake_minimum_required(VERSION 3.10.2)
project("lathe")

add_library(
        lathe
        SHARED
        native-lib.cpp
)

find_library(
        log-lib
        log
)

target_link_libraries(
        lathe
        ${log-lib}
)
