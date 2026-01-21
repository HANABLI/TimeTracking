# CMackeLists.txt for TimeTracking
#
# © 2024 by Hatem Nabli


cmake_minimum_required(VERSION 3.20)
set(this TimeTracking)

set(Headers
    include/TimeTracking/TimeTracking.hpp
)

set(Sources
    src/TimeTracking.cpp
)

add_library(${this} STATIC ${Sources} ${Headers})
set_target_properties(${this} PROPERTIES
    FOLDER Libraries
)

target_include_directories(${this} PUBLIC include)
