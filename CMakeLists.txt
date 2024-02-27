cmake_minimum_required(VERSION 3.19)
project(Stock_Search)

set(CMAKE_CXX_STANDARD 14)

include_directories(Project3)

add_executable(Stock_Search
        Project3/DayData.cpp
        Project3/DayData.h
        Project3/Functions.cpp
        Project3/Functions.h
        Project3/Heap.cpp
        Project3/Heap.h
        Project3/main.cpp
        Project3/MergeSort.cpp
        Project3/Stock.cpp
        Project3/Timer.cpp
        Project3/Timer.h)

add_custom_command(TARGET Stock_Search POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying excel directory..."
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/excel $<TARGET_FILE_DIR:Stock_Search>/excel)
