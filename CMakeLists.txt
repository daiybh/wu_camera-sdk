cmake_minimum_required (VERSION 3.16)

project ("CameraSDK")

add_library(combinedLib INTERFACE)
target_include_directories(combinedLib INTERFACE inc/)

#target_link_directories(combinedLib INTERFACE lib/)

add_executable(test test.cpp)
target_link_libraries(test combinedLib)