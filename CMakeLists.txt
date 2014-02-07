cmake_minimum_required(VERSION 2.8)

project(avcnc)

add_subdirectory(avOS)

include_directories(avOS/include)

add_executable(avcnc main.cpp)
target_link_libraries(avcnc avos)

install(TARGETS avcnc RUNTIME DESTINATION bin)

